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
 * File        : sipm_configuration.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "sipm_configuration.hh"
#include "charging_state.hh"

const std::string SipmConfiguration::INTERNAL_RESISTANCE        = "Rd";
const std::string SipmConfiguration::AVALANCHE_QUENCHING_TIME   = "AQT";
const std::string SipmConfiguration::AVALANCHE_JITTER           = "AJT";

SipmConfiguration::SipmConfiguration()
: SpadConfiguration()
, totalElectricCurrent(1, 0.0)
{
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(INTERNAL_RESISTANCE,           VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(AVALANCHE_QUENCHING_TIME,      VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(AVALANCHE_JITTER,              VarType::DOUBLE));
    
    states.insert(std::pair<State::StateType, State*>(State::CHARGING, new ChargingState(this)));
}

void SipmConfiguration::resetTotalElectricCurrent()
{
    totalElectricCurrent.clear();
    totalElectricCurrent.resize(1, 0.0);
}

void SipmConfiguration::updateTotalElectricCurrent(const Vector< double >& electricCurrent, const double& startTime)
{
    int startIndex = (startTime * 1000.0) + 1;
    int endIndex = startIndex + electricCurrent.size();
    
    if (totalElectricCurrent.size() < endIndex){
        totalElectricCurrent.resize(endIndex, 0.0);
    }
    
    for (int i1 = startIndex, i2 = 0; i1 < endIndex; ++i1, ++i2){
        totalElectricCurrent[i1] += electricCurrent[i2];
    }
}
