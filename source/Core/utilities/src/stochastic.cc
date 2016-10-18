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
 * File        : stochastic.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 9 15:09:28 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "stochastic.hh"
#include "random.hh"

void generateRandom(const unsigned int& count, Vector< double >& out, const double& lambda)
{
    out.resize(count, 0);
    
    for (unsigned int i = 0; i < count; ++i){
        out[i] = RandomGenerator::exponential(lambda);
    }
}

void poissonBirth(const double& rate, const double& timeMax, const double& timeMin, const double& nbProcess, Vector<Vector<double>>& out)
{
    out = Vector<Vector<double>>(1);
    generateRandom(nbProcess, out[0], rate);
    
    while (out.back().min() < (timeMax - timeMin)){
        out.resize(out.size()+1);
        generateRandom(nbProcess, out.back(), rate);
        
        out.back() += out[out.size() - 2];
    }
    
    out.resize(out.size() - 1);
    
    bool changed = true;
    
    for (unsigned int i = 0; i < out.size(); ++i){
        for (unsigned int j = 0; j < out[0].size(); ++j){
            if ((out[i][j] += timeMin) > timeMax){
                out[i][j] = timeMax;   
            }
        }
    }
        
}
