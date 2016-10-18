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
 * File        : sipm.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Mar 15 10:13:19 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "sipm.hh"

#include <math.h>

#include "avalanche.hh"
#include "log.hh"
#include "quench.hh"
#include "random.hh"
#include "sipm_configuration.hh"
#include "var_type.hh"
#include <isensor_configuration.hh>
#include <isimulator.hh>

const double _2_SQRT_2_LOG_2 = 2 * sqrt(2 * log(2));

Sipm::Sipm()
: Spad()
{}

Sipm::~Sipm()
{}

void Sipm::update(const double& elapsed)
{
    time += elapsed;
    if (state == State::QUENCHING && time > 0) {
        state = State::CHARGING;
    }
    if (state == State::CHARGING) {
        double fullOverbias = configuration->getPropertyAs<double>(SpadConfiguration::OVERBIAS);
        double rechargeDelay = configuration->getSimulator()->getQuench()->getPropertyAs<double>(IQuench::RECHARGE_DELAY);
        overbias = fullOverbias * (1 - exp(-time / (rechargeDelay/5.0)));
        if (overbias > 0.95 * fullOverbias) {
            state = State::READY;
        }
    }
}

Avalanche* Sipm::trigger(Particle* particle)
{
    State* currentState = configuration->getState(state);
    Avalanche* avalanche = 0;
    if (currentState->testAvalanche(*particle, overbias)) {
        Vector<double> time, electricCurrent;
        double spadTotalJitter, avalancheTotalJitter;
        calculateAnalogSignal(time, electricCurrent, spadTotalJitter, avalancheTotalJitter);
        particle->addTime(spadTotalJitter);
        getSipmConfiguration()->updateTotalElectricCurrent(electricCurrent, particle->getGlobalTime());
        avalanche = currentState->createAvalanche(particle);        
        if (!avalanche->isMasked()) {
            totalQuenchTime = spadTotalJitter + avalancheTotalJitter;
            quench();
        }
    }
    return avalanche;
}

void Sipm::quench()
{
    state = State::QUENCHING;
    time = - totalQuenchTime;
}

SipmConfiguration* Sipm::getSipmConfiguration() const
{
    SipmConfiguration* config;
    try {
        config = dynamic_cast<SipmConfiguration*>(configuration);
    } catch (std::bad_cast) {
        LOG("The configuration given to the Sipm is not a SipmConfiguration.", 1);
        throw;
    }
    
    return config;
}

void Sipm::calculateAnalogSignal(Vector<double>& time, Vector<double>& electricCurrent, double& spadTotalJitter, double& avalancheTotalJitter) const
{
    double spadJitter = configuration->getPropertyAs<double>(SipmConfiguration::SPAD_JITTER);
    double spadDelay = configuration->getPropertyAs<double>(SipmConfiguration::SPAD_DELAY);
    double internalResistance = configuration->getPropertyAs<double>(SipmConfiguration::INTERNAL_RESISTANCE);
    double avalancheJitter = configuration->getPropertyAs<double>(SipmConfiguration::AVALANCHE_JITTER);
    double avalancheQuenchingTime = configuration->getPropertyAs<double>(SipmConfiguration::AVALANCHE_QUENCHING_TIME);
    double dt = 0.001;
    double tau, i, temp1, temp2;
    
    time.resize(0);
    electricCurrent.resize(0);
    spadTotalJitter = avalancheTotalJitter = -1;
    
    while (spadTotalJitter < 0) {
        spadTotalJitter = 0 + (spadJitter / _2_SQRT_2_LOG_2) * RandomGenerator::rand() + spadDelay;
    }
    tau = spadTotalJitter - 0;
    i = 0;
    while (i < spadTotalJitter) {
        time.push_back(i);
        temp1 = (overbias / internalResistance) / (exp(1) - 1) * (exp((i - 0) / tau) -1);
        electricCurrent.push_back(temp1);
        i += dt;
    }
    while (avalancheTotalJitter < 0) {
        avalancheTotalJitter = spadTotalJitter + (avalancheJitter / _2_SQRT_2_LOG_2) * RandomGenerator::rand() + avalancheQuenchingTime;
    }
    tau = (avalancheTotalJitter - spadTotalJitter) / 5.0;
    temp1 = electricCurrent.back();
    i = spadTotalJitter;
    while (i < avalancheTotalJitter) {
        time.push_back(i);
        temp2 = temp1 * exp(-(i - spadTotalJitter)/tau);
        electricCurrent.push_back(temp2);
        i += dt;
    }
}
