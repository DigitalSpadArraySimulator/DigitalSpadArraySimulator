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
 * File        : dark_count_generator.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 9 15:09:28 2016 -0500 by valentin
 * 
 * FILE_INFO_END */

#include "dark_count_generator.hh"

#include <stdexcept>
#include <algorithm>

#include "dark_count.hh"
#include "isensor.hh"
#include "isensor_configuration.hh"
#include "isimulator.hh"
#include "spad_configuration.hh"
#include "particle.hh"
#include "quench.hh"
#include "spad.hh"
#include "spad_matrix.hh"
#include "stochastic.hh"
#include "var_type.hh"

DarkCountGenerator::DarkCountGenerator(ISimulator const * simulator) 
: IGenerator< DarkCount >(simulator)
{}

DarkCountGenerator::~DarkCountGenerator()
{}

void DarkCountGenerator::generate(Particle* const lastParticle, Vector<Particle*>& out)
{
    double timePeriod = (lastParticle == 0 ? 0 : lastParticle->getGlobalTime());
    Vector<Vector<double>> times;
    double maxTime = simulator->getQuench()->getPropertyAs<double>(IQuench::MAX_EVENT_TIME);
    double rate = simulator->getSensorMatrix()->getPropertyAs<double>(ISensorMatrix::CELL_AREA) * 
                  simulator->getSensorMatrix()->getSensorConfiguration().getPropertyAs<double>(SpadConfiguration::DCR_RATE);
    double depth = -simulator->getSensorMatrix()->getSensorConfiguration().getPropertyAs<double>(SpadConfiguration::SPAD_TOP_DEPTH);
    int dimX = simulator->getSensorMatrix()->getNbSensors().x;
    int dimY = simulator->getSensorMatrix()->getNbSensors().y;
    double nbProcess = dimX * dimY;
    double time;
    Coordinate2D spadCoord;

    maxTime = std::max(maxTime, timePeriod);
    
    poissonBirth(rate, maxTime * 1e-9, 0.0, nbProcess, times);
    
    for (unsigned int i = 0; i < times.size(); ++i){
        for (unsigned int j = 0; j < times[i].size(); ++j){
            time = times[i][j];
            
            if ((time *= 1e9) < maxTime){
                spadCoord = Coordinate2D(j / dimY, j % dimY);
                out.push_back(new DarkCount(time, 
                                            spadCoord, 
                                            Position3D((*simulator->getSensorMatrix())[spadCoord]->getCenter(), 
                                                       depth)));
            }
        }
    }
}


