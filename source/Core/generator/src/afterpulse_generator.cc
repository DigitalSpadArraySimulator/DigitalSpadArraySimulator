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
 * File        : afterpulse_generator.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 10 08:39:50 2016 -0500 by valentin
 * 
 * FILE_INFO_END */

#include "afterpulse_generator.hh"

#include <stdexcept>

#include "afterpulse.hh"
#include "coordinate.hh"
#include "isensor.hh"
#include "isensor_configuration.hh"
#include "spad_configuration.hh"
#include "random.hh"
#include "spad.hh"
#include "spad_matrix.hh"
#include "var_type.hh"
#include "isimulator.hh"


AfterpulseGenerator::AfterpulseGenerator(ISimulator* simulator)
: IGenerator<Afterpulse>(simulator)
{}


AfterpulseGenerator::~AfterpulseGenerator()
{}

Afterpulse* AfterpulseGenerator::createAfterpulse(Particle* parent)
{
    Position2D sensorCenter = (*simulator->getSensorMatrix())[parent->getSensorCoordinate()]->getCenter();
    Position3D position = Position3D(sensorCenter, parent->getPosition().z);
    double lambda = 1.0 / simulator->getSensorMatrix()->getSensorConfiguration().getPropertyAs<double>(SpadConfiguration::AFTERPULSING_DELAY);
    double globalTime = parent->getGlobalTime() + RandomGenerator::exponential(lambda);
    
    return new Afterpulse(parent, globalTime, position);
}

void AfterpulseGenerator::generate(Particle*const source, Vector< Particle* >& out)
{
    out.clearAndDelete();
    
    double prob = simulator->getSensorMatrix()->getSensorConfiguration().getPropertyAs<double>(SpadConfiguration::AFTERPULSING_PROB);
    
    if (RandomGenerator::bernoulli(prob)){
        out.push_back(createAfterpulse(source));
    }
}
