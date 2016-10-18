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
 * File        : spad_configuration.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "spad_configuration.hh"

#include "ready_state.hh"
#include "quenching_state.hh"

const std::string SpadConfiguration::BREAKDOWN_TENSION        = "Vbreak";
const std::string SpadConfiguration::OVERBIAS                 = "Overbias";
const std::string SpadConfiguration::SPAD_DELAY               = "SPADdelay";
const std::string SpadConfiguration::SPAD_JITTER              = "SPADjitter";
const std::string SpadConfiguration::DCR_RATE                 = "DCRrate";
const std::string SpadConfiguration::CROSSTALK_PROB           = "Crosstalk";
const std::string SpadConfiguration::AFTERPULSING_PROB        = "AP_prob";
const std::string SpadConfiguration::AFTERPULSING_DELAY       = "AP_delay";
const std::string SpadConfiguration::TEMPERATURE              = "T";
const std::string SpadConfiguration::SPAD_TOP_DEPTH           = "spadtop";
const std::string SpadConfiguration::SPAD_WELL_DEPTH          = "spadwell";
const std::string SpadConfiguration::PDE_A                    = "PDE_A";
const std::string SpadConfiguration::PDE_B                    = "PDE_B";

// Properties generated from the others
const std::string SpadConfiguration::SPAD_DEP_DEPTH           = "spaddep";

SpadConfiguration::SpadConfiguration()
: ISensorConfiguration()
{
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(BREAKDOWN_TENSION,     VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(OVERBIAS,              VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(SPAD_DELAY,            VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(SPAD_JITTER,           VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(DCR_RATE,              VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(CROSSTALK_PROB,        VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(AFTERPULSING_PROB,     VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(AFTERPULSING_DELAY,    VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(TEMPERATURE,           VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(SPAD_TOP_DEPTH,        VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(SPAD_WELL_DEPTH,       VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(PDE_A,                 VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(PDE_B,                 VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(TEMPERATURE,           VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(SPAD_DEP_DEPTH,        VarType::DOUBLE));
    
    states.insert(std::pair<State::StateType, State*>(State::READY, new ReadyState(this)));
    states.insert(std::pair<State::StateType, State*>(State::QUENCHING, new QuenchingState(this)));
}
