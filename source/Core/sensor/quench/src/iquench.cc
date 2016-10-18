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
 * File        : iquench.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "iquench.hh"

const std::string IQuench::RECHARGE_DELAY = "RechargeDelay";
const std::string IQuench::DEAD_TIME = "Dead_time";
const std::string IQuench::RESET_TIME = "Reset_time";
const std::string IQuench::MAX_EVENT_TIME = "Max_event_time";

IQuench::IQuench()
: IConfigurable()
{
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(RECHARGE_DELAY, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(DEAD_TIME, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(RESET_TIME, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(MAX_EVENT_TIME, VarType::DOUBLE));
}
