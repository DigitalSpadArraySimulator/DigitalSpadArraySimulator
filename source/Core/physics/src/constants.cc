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
 * File        : constants.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 16:57:33 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "constants.hh"
#include "string_cast.hh"

Map<std::string, double> PhysicsConstants::constants = Map<std::string, double>();

const std::string PhysicsConstants::ELECTRON_CHARGE             = "q";
const std::string PhysicsConstants::BOLTZMANN_CONSTANT          = "k";
const std::string PhysicsConstants::BOLTZMANN_CONSTANT_J        = "k_JK";
const std::string PhysicsConstants::VOID_PERMITTIVITY           = "E0";
const std::string PhysicsConstants::ELECTRON_REST_MASS          = "m0";
const std::string PhysicsConstants::PlANCK_SPEED_LIGHT          = "hc";

const double electronCharge = 1.6e-19;
const double boltzmannConstant = 0.00008617;
const double boltzmannConstantJ = 1.38e-023;
const double voidPermittivity = 0.0000000000000885;
const double electronRestMass = 9.11e-031;
const double planckSpeedLight = 1.23984193;

void PhysicsConstants::init()
{
    constants.insert(std::pair<std::string, double>(ELECTRON_CHARGE, electronCharge));
    constants.insert(std::pair<std::string, double>(BOLTZMANN_CONSTANT, boltzmannConstant));
    constants.insert(std::pair<std::string, double>(BOLTZMANN_CONSTANT_J, boltzmannConstantJ));
    constants.insert(std::pair<std::string, double>(VOID_PERMITTIVITY, voidPermittivity));
    constants.insert(std::pair<std::string, double>(ELECTRON_REST_MASS, electronRestMass));
    constants.insert(std::pair<std::string, double>(PlANCK_SPEED_LIGHT, planckSpeedLight));
}

void PhysicsConstants::init(const Map<std::string, std::string>& newConstants)
{
    init();
    Map<std::string, std::string>::const_iterator it;
    double value;
    
    for (it = newConstants.begin(); it != newConstants.end(); ++it) {
        castTo<double>(it->second, value);
        if (constants.find(it->first) != constants.end()) {
            constants[it->first] = value;
        } else {
            constants.insert(std::pair<std::string, double>(it->first, value));
        }
    }
}

void PhysicsConstants::reset()
{
    constants.clear();
}

double PhysicsConstants::get(const std::string& constant)
{
    std::map<std::string, double>::iterator it = constants.find(constant);
    double result = 0;
    if (it != constants.end()) {
        result = it->second;
    }
    return result;
}
