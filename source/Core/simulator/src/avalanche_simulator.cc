/* FILE_INFO_START
 * Copyright (C) 2016 
 * 
 * ***********************************************************************
 * This file is part of SpadSimulator
 * 
 * SpadSimulator is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * SpadSimulator is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SpadSimulator.  If not, see <http://www.gnu.org/licenses/>.
 * ***********************************************************************
 * 
 * File        : avalanche_simulator.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 3 14:30:27 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "afterpulse_generator.hh"
#include "avalanche.hh"
#include "avalanche_simulator.hh"
#include "array_algorithm.hh"
#include "constants.hh"
#include "crosstalk_generator.hh"
#include "dark_count_generator.hh"
#include "isensor.hh"
#include "isensor_configuration.hh"
#include "spad_configuration.hh"
#include "particle.hh"
#include "photon.hh"
#include "quench.hh"
#include "quench_factory.hh"
#include "silicon.hh"
#include "silicon_factory.hh"
#include "spad.hh"
#include "spad_factory.hh"
#include "spad_matrix.hh"
#include "spad_matrix_factory.hh"
#include <isensor_matrix_factory.hh>
#include "var_type.hh"
#include "log.hh"
#include <iostream>

AvalancheSimulator::AvalancheSimulator() 
: ISimulator()
, apGen(0)
, ctGen(0)
, dcGen(0)
, skipAvalancheOnZeroParticles(true)
{
    PhysicsConstants::init();
}

AvalancheSimulator::~AvalancheSimulator() {}

void AvalancheSimulator::init(const Map<std::string, std::string>& siliconProperties,
                              const Map<std::string, std::string>& quenchProperties,
                              const Map<std::string, std::string>& sensorProperties,
                              const Map<std::string, std::string>& matrixProperties)
{
    if (!siliconFactory) {
        setSiliconFactory(new SiliconFactory());
    }
    if (!quenchFactory) {
        setQuenchFactory(new QuenchFactory());
    }
    if (!matrixFactory) {
        setSensorMatrixFactory(new SpadMatrixFactory());
    }
    ISimulator::init(siliconProperties, quenchProperties, sensorProperties, matrixProperties);
    
    if (!apGen) {
        setAfterpulseGenerator(new AfterpulseGenerator(this));
    }
    if (!ctGen) {
        setCrosstalkGenerator(new CrosstalkGenerator(this));
    }
    if (!dcGen) {
        setDarkCountGenerator(new DarkCountGenerator(this));
    }
}

void AvalancheSimulator::setAfterpulseGenerator(IGenerator< Afterpulse >* apGen)
{
    if(!apGen){
        throw std::invalid_argument("The given IGenerator is null");
    }
    
    if (apGen != this->apGen){
        if (this->apGen){
            delete this->apGen;
        }
        this->apGen = apGen;
    }
}

void AvalancheSimulator::setCrosstalkGenerator(IGenerator< Crosstalk >* ctGen)
{
    if(!ctGen){
        throw std::invalid_argument("The given IGenerator is null");
    }
    
    if (ctGen != this->ctGen){
        if (this->ctGen){
            delete this->ctGen;
        }
        this->ctGen = ctGen;
    }
}

void AvalancheSimulator::setDarkCountGenerator(IGenerator< DarkCount >* dcGen)
{
    if(!dcGen){
        throw std::invalid_argument("The given IGenerator is null");
    }
    
    if (dcGen != this->dcGen){
        if (this->dcGen){
            delete this->dcGen;
        }
        this->dcGen = dcGen;
    }
}

void AvalancheSimulator::simulateAll(const Vector<Photon*>& photons, Vector<Avalanche*>& avalanches)
{
    Vector<Particle*> particles;
    
    simulateAbsorption(photons, particles);
    simulateRandomWalk(particles);
    simulateAvalanche(particles, avalanches);
}

void AvalancheSimulator::simulateAbsorption(const Vector<Photon*>& photons, Vector<Particle*>& absorbedParticle) const
{
    Vector<Photon*>::const_iterator it;
    Photon* photon;
    
    for (it = photons.begin(); it != photons.end(); it++){
        photon = *it;
        silicon->calculatePhotonAbsorptionPoint(*photon);
        
        if (matrix->isAbsorbed(*photon)){
            absorbedParticle.push_back(new Particle(*photon));
        }
    }
}

void AvalancheSimulator::simulateRandomWalk(Vector<Particle*>& particles) const
{
    Vector<Particle*> top, dep, bottom;
    matrix->sortByDepth(particles, top, dep, bottom);
    
    particles.clearAndDelete();
    particles = dep;
    
    matrix->randomWalk(top, true, particles);
    matrix->randomWalk(bottom, false, particles);
    
    dep.clear();
    top.clearAndDelete();
    bottom.clearAndDelete();
}

void AvalancheSimulator::simulateAvalanche(Vector<Particle*>& particles, Vector<Avalanche*>& avalanches)
{
    avalanches.clearAndDelete();
    
    if (skipAvalancheOnZeroParticles && particles.empty()){
        return;
    }
    
    Vector<Particle*>::iterator it;
    Particle* particle;
    ISensor* sensor;
    Avalanche* avalanche;
    double currentTime = 0;
    double elapsed;
    
    HeapSort::heapSort(particles);
    simulateDarkCount(particles);

    int startSize = particles.size();
    double APprob = matrix->getSensorConfiguration().getPropertyAs<double>(SpadConfiguration::AFTERPULSING_PROB);
    double CTprob = matrix->getSensorConfiguration().getPropertyAs<double>(SpadConfiguration::CROSSTALK_PROB);
    int estimatedSize = startSize + 5*startSize*APprob+ 5*startSize*CTprob;
    if (estimatedSize<100) {
        estimatedSize = 100;
    }
    particles.reserve(estimatedSize);

    for (it = particles.begin(); it != particles.end();){
        particle = *it;
        
        elapsed = particle->getGlobalTime() - currentTime;
        currentTime += elapsed;
        matrix->update(elapsed);
        try {
            sensor = (*matrix)[particle->getSensorCoordinate()];
        }
        catch (std::out_of_range) {
            Coordinate2D coord = particle->getSensorCoordinate();
            LOG_STREAM(1) << "Coordinates : " << coord.x << " " << coord.y << std::endl;
            LOG_STREAM(1) << "Type : " << particle->getParticleType() << std::endl;
            __throw_exception_again;
        }

        avalanche = sensor->trigger(particle);
        
        if (avalanche){
            avalanches.push_back(avalanche);
            if (!avalanche->isMasked()){
                simulateCrosstalk(particle, particles);
                simulateAfterpulse(particle, particles);
            }
            it = particles.erase(it);
        } else {
            it = particles.eraseAndDelete(it);
        }
    }
}

void AvalancheSimulator::simulateAfterpulse(Particle* particle, Vector< Particle* >& particles)
{
    Vector<Particle*> afterpulses;
    Vector<Particle*>::iterator it;
    Particle* afterpulse;
    
    apGen->generate(particle, afterpulses);
    
    for (it = afterpulses.begin(); it != afterpulses.end(); ){
        afterpulse = *it;
        Dichotomic::insert(particles, afterpulse);
        it = afterpulses.erase(it);
    }
}

void AvalancheSimulator::simulateCrosstalk(Particle* particle, Vector<Particle*>& particles)
{
    Vector<Particle*> crosstalks;
    Vector<Particle*>::iterator it;
    Particle* crosstalk;
    
    ctGen->generate(particle, crosstalks);
    
    for (it = crosstalks.begin(); it != crosstalks.end(); ){
        crosstalk = *it;
        Dichotomic::insert(particles, crosstalk);
        it = crosstalks.erase(it);
    }
}

void AvalancheSimulator::simulateDarkCount(Vector<Particle*>& particles)
{
    double quenchingTime = quench->getPropertyAs<double>(IQuench::RECHARGE_DELAY) + quench->getPropertyAs<double>(IQuench::DEAD_TIME);
    Particle* lastParticle = (particles.empty() ? 0 : particles.back());//->getGlobalTime() + quenchingTime
    Vector<Particle*> darkCounts;
    Vector<Particle*>::iterator it;
    Particle* darkcount;
    
    dcGen->generate(lastParticle, darkCounts);
    
    for (it = darkCounts.begin(); it != darkCounts.end();){
        darkcount = *it;
        Dichotomic::insert(particles, darkcount);
        it = darkCounts.erase(it);
    }
}
