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
 * File        : spad.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Feb 26 09:44:39 2016 -0500 by valentin
 * 
 * FILE_INFO_END */

#include "spad.hh"

#include "avalanche.hh"
#include "isensor_configuration.hh"
#include "isimulator.hh"
#include "pde_behavior.hh"
#include "photon.hh"
#include "polygon.hh"
#include "quench.hh"
#include "random.hh"
#include "spad_configuration.hh"
#include "var_type.hh"

Spad::Spad()
: ISensor()
{}

Spad::~Spad()
{}

bool Spad::isAbsorbed(const Photon& photon) const
{
    bool result = false;
    if(polygon->contains(photon.getPenetrationPoint()) 
       && polygon->contains(photon.getAbsortptionPoint())) {
        result = true;
    }
    return result;
}

bool Spad::randomWalk(Particle& particle, const double& meanLifetime, const bool& fromTop, const double& tau, const double& scalingFactor) const
{
    double lifetime = RandomGenerator::exponential(1/meanLifetime);
    double time = 0;
    bool depReached = false;
    double z;
    double spadStart = 0.0;
    double depStart = -configuration->getPropertyAs<double>(SpadConfiguration::SPAD_TOP_DEPTH);
    double depEnd = -configuration->getPropertyAs<double>(SpadConfiguration::SPAD_DEP_DEPTH);
    double spadEnd = -configuration->getPropertyAs<double>(SpadConfiguration::SPAD_WELL_DEPTH);
    
    while (!depReached) {
        time += particle.MoveRandomly(tau, scalingFactor);
        if (time > lifetime // busted time
            || !polygon->contains(particle.getPosition())) { // busted out (side)
            break;
        }
        z = particle.getPosition().z;
        if (fromTop) {
            if (z > spadStart) {
                break; // busted out (top)
            } else if(z <= depStart) {
                particle.setDepth(depStart);
                depReached = true;
            }
        } else {
            if (z < spadEnd) {
                break; // busted out (bottom)
            } else if(z >= depEnd) {
                particle.setDepth(depEnd);
                depReached = true;
            }
        }
    }
    return depReached;
}

void Spad::update(const double& elapsed)
{
    time += elapsed;
    if (state != State::READY && time > 0) {
        state = State::READY;
        overbias = configuration->getPropertyAs<double>(SpadConfiguration::OVERBIAS);
    }
}

Avalanche* Spad::trigger(Particle* particle)
{
    State* currentState = configuration->getState(state);
    Avalanche* avalanche = 0;
    if (currentState->testAvalanche(*particle, overbias)) {
        avalanche = currentState->createAvalanche(particle);
        if(!avalanche->isMasked()) {
            quench();
        }
    }
    return avalanche;
}

void Spad::quench()
{
    state = State::QUENCHING;
    overbias = 0;
    IQuench const * quench = configuration->getSimulator()->getQuench();
    time = -(quench->getPropertyAs<double>(IQuench::DEAD_TIME) +
             quench->getPropertyAs<double>(IQuench::RECHARGE_DELAY));
}

void Spad::reset()
{
    state = State::READY;
    time = 0;
    overbias = configuration->getPropertyAs<double>(SpadConfiguration::OVERBIAS);
}

