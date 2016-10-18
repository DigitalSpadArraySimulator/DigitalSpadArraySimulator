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
 * File        : isensor_factory.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "isensor_factory.hh"

#include <math.h>
#include <stdexcept>

#include "isensor_configuration.hh"

ISensorFactory::ISensorFactory()
: sensorConfiguration(0)
{}

ISensorFactory::~ISensorFactory()
{
    // Will be deleted by the ISensorMatrix
    sensorConfiguration = 0;
}

void ISensorFactory::setSensorConfiguration(ISensorConfiguration* sensorConfiguration)
{
    if (!sensorConfiguration) {
        throw std::invalid_argument("The ISensorConfiguration can't be null!");
    }
    if (sensorConfiguration != this->sensorConfiguration) {
        if (this->sensorConfiguration) {
            delete this->sensorConfiguration;
        }
        this->sensorConfiguration = sensorConfiguration;
    }
    calculateCorrectedRadius();
}

void ISensorFactory::calculateCorrectedRadius()
{
    int nbVertices = sensorConfiguration->getPropertyAs<int>(ISensorConfiguration::NB_VERTICES);
    double phi = M_PI / nbVertices;
    double radius = sensorConfiguration->getPropertyAs<double>(ISensorConfiguration::RADIUS_TO_SIDES);
    double correctedRadius = abs(radius / cos(phi));
    
    sensorConfiguration->setProperty(ISensorConfiguration::ANGLE, new VarType(phi));
    sensorConfiguration->setProperty(ISensorConfiguration::RADIUS_TO_VERTICES, new VarType(correctedRadius));
}
