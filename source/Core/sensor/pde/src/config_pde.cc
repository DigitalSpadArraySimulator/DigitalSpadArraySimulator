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
 * File        : config_pde.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 16:57:33 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "config_pde.hh"
#include <math.h>

ConfigPDE::ConfigPDE(const double& pdeA, const double& pdeB, const double& spadDepth) 
: PDEBehavior(false)
, pdeA(pdeA)
, pdeB(pdeB)
, spadDepth(spadDepth)
{}

void ConfigPDE::calculateDepletionZone(const double&, double& depStart, double& depEnd) const
{
    depStart = 0;
    depEnd = spadDepth;
}

void ConfigPDE::calculateAvalancheProbabilities(const double& overbias, 
                                                Vector<double>& electronProb, 
                                                Vector<double>& holeProb, 
                                                Vector<double>& probDepth) const
{
    electronProb.clear();
    holeProb.clear();
    probDepth.clear();
    
    double pde = pdeA * (1 - exp(-pdeB * overbias));
    
    electronProb.push_back(pde);
    holeProb.push_back(0);
    probDepth.push_back(spadDepth);
}

