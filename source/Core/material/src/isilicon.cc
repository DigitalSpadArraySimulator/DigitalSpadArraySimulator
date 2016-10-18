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
 * File        : isilicon.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "isilicon.hh"

#include "absorption_behavior.hh"
#include "photon.hh"
#include "random.hh"

const std::string ISilicon::DOPING_TYPE                = "type";
const std::string ISilicon::ALPHA                      = "alpha";
const std::string ISilicon::WELL_DOPING                = "Nwell";
const std::string ISilicon::TOP_DOPING                 = "Ntop";
const std::string ISilicon::DOPING_GRADIENT            = "a";
const std::string ISilicon::N_ZONE_ELECTRON_MOBILITY   = "mun_N";
const std::string ISilicon::N_ZONE_HOLE_MOBILITY       = "mup_N";
const std::string ISilicon::P_ZONE_ELECTRON_MOBILITY   = "mun_P";
const std::string ISilicon::P_ZONE_HOLE_MOBILITY       = "mup_P";
const std::string ISilicon::INTRINSIC_CARRIERS         = "ni";
const std::string ISilicon::RELATIVE_PERMITTIVITY      = "Er";
const std::string ISilicon::MASS_CONDUCTIVITY_ELECTRON = "mce";
const std::string ISilicon::MASS_CONDUCTIVITY_HOLE     = "mch";

ISilicon::ISilicon()
: IConfigurable()
, absorptionBehavior(0)
{
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(DOPING_TYPE, VarType::ENUM));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(ALPHA, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(WELL_DOPING, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(TOP_DOPING, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(DOPING_GRADIENT, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(N_ZONE_ELECTRON_MOBILITY, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(N_ZONE_HOLE_MOBILITY, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(P_ZONE_ELECTRON_MOBILITY, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(P_ZONE_HOLE_MOBILITY, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(INTRINSIC_CARRIERS, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(RELATIVE_PERMITTIVITY, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(MASS_CONDUCTIVITY_ELECTRON, VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(MASS_CONDUCTIVITY_HOLE, VarType::DOUBLE));
}

ISilicon::~ISilicon()
{
    if (absorptionBehavior) {
        delete absorptionBehavior;
        absorptionBehavior = 0;
    }
}

void ISilicon::calculatePhotonAbsorptionPoint(Photon& photon)
{
    double lambda = absorptionBehavior->getAbsorptionCoefficient(photon.getWavelength());
    double depth = RandomGenerator::exponential(lambda/10000.0);
    photon.calculateAbsorptionPoint(depth);
}
