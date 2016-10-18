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
 * File        : state.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 9 09:29:49 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include <math.h>
#include <stdexcept>

#include "array_algorithm.hh"
#include "random.hh"
#include "state.hh"
#include "particle.hh"
#include "avalanche.hh"
#include "spad.hh"
#include "var_type.hh"
#include <iconfigurable.hh>
#include <spad_configuration.hh>

const double jitterConst = 2 * sqrt(2 * log(2));

State::State(const State::StateType& type, ISensorConfiguration const * sensorConfig) 
: type(type)
, sensorConfig(sensorConfig)
{
    if (!sensorConfig) {
        throw std::invalid_argument("The given configuration is null");
    }
}

bool State::calculateAvalancheProbability(const Particle& particle, 
                                          const Vector<double>& probElectron, 
                                          const Vector<double>& probHole,
                                          const Vector<double>& depthProb) const
{
    int index = Dichotomic::findSmallerClosestIndex(depthProb, particle.getPosition().z);
    bool triggerHole = RandomGenerator::bernoulli(probHole[index]);
    bool triggerElectron = RandomGenerator::bernoulli(probElectron[index]);
    return triggerHole || triggerElectron;
}


double State::calculateJitterDelay(double spadJitter, double spadDelay) const
{
    return RandomGenerator::normal(spadDelay, (spadJitter / jitterConst));
}

Avalanche* State::createAvalanche(Particle* particle) const
{
    double jitter = calculateJitterDelay(sensorConfig->getPropertyAs<double>(SpadConfiguration::SPAD_JITTER),
                                         sensorConfig->getPropertyAs<double>(SpadConfiguration::SPAD_DELAY));
    bool isMasked = createMaskedAvalanche();
    return new Avalanche(particle, jitter, isMasked);
}

bool State::testAvalanche(const Particle& particle, const double&) const {
    return calculateAvalancheProbability(particle,
                                         sensorConfig->getReadyProbE(),
                                         sensorConfig->getReadyProbH(), 
                                         sensorConfig->getReadyDepths());
}
