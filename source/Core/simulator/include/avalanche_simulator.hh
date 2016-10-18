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
 * File        : avalanche_simulator.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 3 14:30:27 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef AVALANCHE_SIMULATOR_SIMULATOR_H
#define AVALANCHE_SIMULATOR_SIMULATOR_H

#include <string>

#include "map.hh"
#include "vector.hh"
#include "iconfigurable_factory.hh"
#include "isimulator.hh"

template <typename T> class IGenerator;

class Afterpulse;
class Avalanche;
class Crosstalk;
class DarkCount;
class SpadMatrix;
class Photon;
class Particle;
class ISilicon;
class IQuench;

/**
 * @brief Class that can simulates steps from the absorption in the sensor to the avalanche triggering.
 */
class AvalancheSimulator : public ISimulator {
private:
    AvalancheSimulator(const AvalancheSimulator&);
    AvalancheSimulator& operator=(const AvalancheSimulator&);
    
protected:
    /**
     * @brief The generator used to create afterpulses.
     */
    IGenerator<Afterpulse>* apGen;
    
    /**
     * @brief The generator used to create crosstalks.
     */
    IGenerator<Crosstalk>* ctGen;
    
    /**
     * @brief The generator used to create dark counts.
     */
    IGenerator<DarkCount>* dcGen;
    
    /**
     * @brief If true, the avalanche simulation will be skiped when there are no particle from the start.
     * 
     * If false, dark counts will be generated and the avalanche simulation will continue normally.
     */
    bool skipAvalancheOnZeroParticles;
    
    /**
     * @brief Simulate afterpulses based on a particle and add them in the particles.
     * 
     * @warning When adding particles in the vector, you must preserve the chronological order.
     * 
     * @see Dichotomic::insert
     * 
     * @param particle The particle that triggered an avalanche.
     * @param[in,out] particles The particles that have not been simulated yet.
     */
    void simulateAfterpulse(Particle* particle, Vector<Particle*>& particles);
    
    /**
     * @brief Simulate crosstalks based on a particle and add them in the particles.
     * 
     * @warning When adding particles in the vector, you must preserve the chronological order.
     * 
     * @see Dichotomic::insert
     * 
     * @param particle The particle that triggered an avalanche.
     * @param[in,out] particles The particles that have not been simulated yet.
     */
    void simulateCrosstalk(Particle* particle, Vector<Particle*>& particles);
    
    /**
     * @brief Simulate dark counts and add them in the particles.
     * 
     * @warning When adding particles in the vector, you must preserve the chronological order.
     * 
     * @see Dichotomic::insert
     * 
     * @param[in,out] particles The particles that have not been simulated yet.
     */
    void simulateDarkCount(Vector<Particle*>& particles);
    
public:
    /**
     * @brief Default constructor
     */
    AvalancheSimulator();
    /**
     * @brief Destructor
     */
    ~AvalancheSimulator();
    
    /**
     * @brief Initialize every components in the simulator
     * 
     * @warning If not previously set, the following object will be used:
     * SiliconFactory, QuenchFactory, SpadMatrixFactory, AfterpulseGenerator, CrosstalkGenerator, DarkCountGenerator
     * 
     * @param siliconProperties The silicon properties <PropertyName, PropertyValue>
     * @param quenchProperties The quench properties <PropertyName, PropertyValue>
     * @param sensorProperties The sensor properties <PropertyName, PropertyValue>
     * @param matrixProperties The matrix properties <PropertyName, PropertyValue>
     */
    virtual void init(const Map<std::string, std::string>& siliconProperties,
                      const Map<std::string, std::string>& quenchProperties,
                      const Map<std::string, std::string>& sensorProperties,
                      const Map<std::string, std::string>& matrixProperties) override;
    
    /**
     * @brief Set a specific afterpulse generator.
     * 
     * @param apGen The afterpulse generator.
     */
    virtual void setAfterpulseGenerator(IGenerator<Afterpulse>* apGen);
    
    /**
     * @brief Set a specific crosstalk generator.
     * 
     * @param ctGen The crosstalk generator.
     */
    virtual void setCrosstalkGenerator(IGenerator<Crosstalk>* ctGen);
    
    /**
     * @brief Set a specific dark count generator.
     * 
     * @param dcGen The dark count generator.
     */
    virtual void setDarkCountGenerator(IGenerator<DarkCount>* dcGen);
    
    /**
     * @brief Simulate the absorption, the randomWalk and the avalanches processes.
     * 
     * @param photons The photons that hit the matrix.
     * @param[out] avalanches The avalanche generated.
     */
    virtual void simulateAll(const Vector<Photon*>& photons, Vector<Avalanche*>& avalanches) override;
    
    /**
     * @brief Simulate the absorption of photons into the silicon sensor.
     * 
     * Will only keep particles that have penetrate in the sensor surface and that were still inside after the absorption.
     * 
     * @param photons The photons that hit the matrix.
     * @param[out] absorbedParticle The particle that were absorbed in the silicon.
     */
    virtual void simulateAbsorption(const Vector<Photon*>& photons, Vector<Particle*>& absorbedParticle) const override;
    
    /**
     * @brief Simulate the random walk for the particle.
     * 
     * First the particles will be split into 3 groups depending on where they were absorbed (top, depletion zone and bottom).
     * 
     * For the ones in the top and bottom, make them move randomly to try to reach the depletion zone.
     * 
     * @warning The particles that didn't reach the depletion zone will be deleted.
     * 
     * @param[in,out] particles Take the absorbed particles and discard the ones that didn't reach the depletion zone
     */
    virtual void simulateRandomWalk(Vector<Particle*>& particles) const override;
    
    /**
     * @brief Simulate avalanche from particles that reached the depletion zone
     * 
     * @warning Every particle that did not create an avalanche will be deleted. particles will be empty after this call.
     * 
     * @param particles The particles that reached the depletion zone
     * @param[out] avalanches The avalanche generated
     */
    virtual void simulateAvalanche(Vector<Particle*>& particles, Vector<Avalanche*>& avalanches) override;
};

#endif //AVALANCHE_SIMULATOR_SIMULATOR_H