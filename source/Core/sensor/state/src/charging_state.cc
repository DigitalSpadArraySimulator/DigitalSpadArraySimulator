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
 * File        : charging_state.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Mar 15 10:13:19 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "charging_state.hh"
#include "pde_behavior.hh"
#include "vector.hh"
#include <iconfigurable.hh>
#include <isensor_configuration.hh>

ChargingState::ChargingState(ISensorConfiguration const * sensorConfig)
: State(State::CHARGING, sensorConfig)
{

}


bool ChargingState::testAvalanche(const Particle& particle, const double& overbias) const
{
    Vector<double> probElectron, probHole, depthProb;
    
    sensorConfig->getPDE().calculateAvalancheProbabilities(overbias, probElectron, probHole, depthProb);
    
    return calculateAvalancheProbability(particle, probElectron, probHole, depthProb);
}
