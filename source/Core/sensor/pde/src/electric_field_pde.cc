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
 * File        : electric_field_pde.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Mar 8 09:23:22 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "electric_field_pde.hh"
#include "differential_equation.hh"

ElectricFieldPDE::ElectricFieldPDE(const double& topDepth, const Vector<double>& electricField, const Vector<double>& depths)
: PDEBehavior(true)
, topDepth(topDepth)
, electricField(electricField)
, depths(depths)
{
    dz = (depths[2] - depths[1]) * 1e-4;
}

ElectricFieldPDE::~ElectricFieldPDE()
{
    electricField.clear();
    depths.clear();
}

void ElectricFieldPDE::calculateAvalancheProbabilities(const double&, 
                                                       Vector<double>& electronProb, 
                                                       Vector<double>& holeProb, 
                                                       Vector<double>& probDepth) const
{
    calculateProbabilitiesFromElectricField(electricField, depths, dz, electronProb, holeProb);
    probDepth = depths;
}

void ElectricFieldPDE::calculateDepletionZone(const double&, double& depStart, double& depEnd) const
{
    depStart = topDepth;
    depEnd = depths.back() - depths.front() + depStart;
}
