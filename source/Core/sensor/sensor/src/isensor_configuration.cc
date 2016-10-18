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
 * File        : isensor_configuration.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "isensor_configuration.hh"
#include "pde_behavior.hh"

const std::string ISensorConfiguration::NB_VERTICES              = "vertices";
const std::string ISensorConfiguration::RADIUS_TO_SIDES          = "radius";
const std::string ISensorConfiguration::RADIUS_TO_VERTICES       = "correctedRadius";
const std::string ISensorConfiguration::ANGLE                    = "angle";

ISensorConfiguration::ISensorConfiguration() 
: IConfigurable()
, pde(0)
, simulator(0)
, states()
, readyProbE()
, readyProbH()
, readyDepths()
{
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(NB_VERTICES,           VarType::INT));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(RADIUS_TO_SIDES,       VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(RADIUS_TO_VERTICES,    VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(ANGLE,                 VarType::DOUBLE));
}

ISensorConfiguration::~ISensorConfiguration()
{
    states.clearAndDeleteValues();
    
    if (pde) {
        delete pde;
    }
}

State* ISensorConfiguration::getState(const State::StateType& stateType) const
{
    Map<State::StateType, State*>::const_iterator it;
    State* state = 0;
    it = states.find(stateType);
    
    if (it != states.end()) {
        state = it->second;
    }
    
    return state;
}
