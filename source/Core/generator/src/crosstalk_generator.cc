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
 * File        : crosstalk_generator.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 10 07:39:28 2016 -0500 by valentin
 * 
 * FILE_INFO_END */

#include "crosstalk_generator.hh"

#include <stdexcept>
#include <algorithm>

#include "crosstalk.hh"
#include "isensor.hh"
#include "isensor_configuration.hh"
#include "isimulator.hh"
#include "spad_configuration.hh"
#include "particle.hh"
#include "random.hh"
#include "spad.hh"
#include "spad_matrix.hh"
#include "var_type.hh"


const double lightspeed = 299792458 * 10e6 / 10e9 / 3.6; // (Approximate speed of light in silicon)

CrosstalkGenerator::CrosstalkGenerator(ISimulator const * simulator) 
: IGenerator<Crosstalk>(simulator)
{}

CrosstalkGenerator::~CrosstalkGenerator()
{}

void CrosstalkGenerator::initProbs(Map< int, double >& probs) const
{
    probs.clear();
    
    double prob1 = simulator->getSensorMatrix()->getSensorConfiguration().getPropertyAs<double>(SpadConfiguration::CROSSTALK_PROB);
    double prob2 = prob1 * prob1;
    
    probs.insert(std::pair<int, double>(1, prob1));
    probs.insert(std::pair<int, double>(2, prob2));
}

void CrosstalkGenerator::generateCrosstalkLoop(Particle*const source, 
                                               Vector< Particle* >& out, 
                                               const Map< int, double >& probs, 
                                               const int& opticalCrosstalkRange)
{
    out.clearAndDelete();
    
    int xStart, xEnd, yStart, yEnd, particleX, particleY, distance;
    double prob;
    
    particleX = source->getSensorCoordinate().x;
    particleY = source->getSensorCoordinate().y;
    xStart = std::max(0, particleX - opticalCrosstalkRange);
    xEnd = std::min(simulator->getSensorMatrix()->getNbSensors().x - 1, particleX + opticalCrosstalkRange);
    yStart = std::max(0, particleY - opticalCrosstalkRange);
    yEnd = std::min(simulator->getSensorMatrix()->getNbSensors().y - 1, particleY + opticalCrosstalkRange);
    
    for (int x = xStart; x <= xEnd; ++x){
        for (int y = yStart; y <= yEnd; ++y){
            distance = abs(x - particleX) + abs(y - particleY);
            
            if (probs.find(distance) != probs.end()){
                prob = probs.at(distance);
            } else {
                prob = 0;
            }
            
            if (RandomGenerator::bernoulli(prob)){
                out.push_back(createCrosstalk(source, Coordinate2D(x, y)));
            }
        }
    }
}

void CrosstalkGenerator::generate(Particle* const source, Vector<Particle*>& out)
{
    out.clearAndDelete();
    
    Map<int, double> probs;
    initProbs(probs);
    generateCrosstalkLoop(source, out, probs, 1);
}

Crosstalk* CrosstalkGenerator::createCrosstalk(Particle* parent, const Coordinate2D& spadCoord)
{
    double spad_top_depth = -simulator->getSensorMatrix()->getSensorConfiguration().getPropertyAs<double>(SpadConfiguration::SPAD_TOP_DEPTH);
    Position2D center = (*simulator->getSensorMatrix())[spadCoord]->getCenter();
    Position3D position (center, spad_top_depth);
    double distance = position.calculateDistance(parent->getPosition());
    distance += simulator->getSensorMatrix()->getPropertyAs<double>(ISensorMatrix::PITCH) * std::abs(RandomGenerator::normal(1));
    double time = distance / lightspeed + parent->getGlobalTime();
    
    return new Crosstalk(parent, time, spadCoord, position);
}

