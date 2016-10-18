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
 * File        : isensor.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "isensor.hh"

#include <stdexcept>

#include "polygon.hh"

ISensor::ISensor()
: ISensor(0)
{}

ISensor::ISensor(ISensorConfiguration* configuration)
: polygon(0)
, configuration(configuration)
, time(0)
, state(State::READY)
{}

ISensor::~ISensor()
{
    if (polygon) {
        delete polygon;
        polygon = 0;
    }
    
    // The configuration will be deleted by the matrix
    if (configuration) {
        configuration = 0;
    }
}

void ISensor::update(const double& elapsed)
{
    time += elapsed;
}

void ISensor::reset()
{
    state = State::READY;
    time = 0;
}

const Position2D& ISensor::getCenter() const
{
    if (!polygon) {
        throw std::logic_error("The polygon was not created.");
    }
    
    return polygon->getCenter();
}

