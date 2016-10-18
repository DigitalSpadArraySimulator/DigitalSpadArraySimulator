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
 * File        : junction_pde.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 16:57:33 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "junction_pde.hh"

#include <math.h>
#include <stdexcept>

#include "constants.hh"
#include "differential_equation.hh"
#include "isilicon.hh"
#include "var_type.hh"

const double dz = 1e-5;

JunctionPDE::JunctionPDE(ISilicon const * silicon, const double& temperature, const double& breakdownTension, const double& topDepth)
: PDEBehavior(true)
, silicon(silicon)
, temperature(temperature)
, breakdownTension(breakdownTension)
, topDepth(topDepth)
{
    if (!silicon) {
        throw std::invalid_argument("The given ISilicon is null");
    }
}

JunctionPDE::~JunctionPDE()
{
    silicon = 0;
}


void JunctionPDE::calculateElectricField(const double& overbias, Vector< double >& electricField, Vector< double >& depths) const 
{
    double k = PhysicsConstants::get(PhysicsConstants::BOLTZMANN_CONSTANT);
    double q = PhysicsConstants::get(PhysicsConstants::ELECTRON_CHARGE);
    double E0 = PhysicsConstants::get(PhysicsConstants::VOID_PERMITTIVITY);
    double a = silicon->getPropertyAs<double>(ISilicon::DOPING_GRADIENT);
    double Er = silicon->getPropertyAs<double>(ISilicon::RELATIVE_PERMITTIVITY);
    double ni = silicon->getPropertyAs<double>(ISilicon::INTRINSIC_CARRIERS);
    double wellDoping = silicon->getPropertyAs<double>(ISilicon::WELL_DOPING);
    double temp;
    
    double Vg = (2 * k * temperature / 3) * log(pow(a, 2) * Er * E0 * k * temperature / (q * pow(ni, 3) * 8));
    double DEPdz = 1e4 * sqrt(2 * Er * E0 * (Vg + breakdownTension + overbias) / (q * wellDoping));
    
    for (double z = -DEPdz/2; z <= DEPdz/2; z += dz) {
        temp = -(q * a / (2 * Er * E0)) * (pow(1e-4 * DEPdz / 2, 2) - pow(1e-4 * z, 2));
        electricField.push_back(temp);
        depths.push_back(z);
    }
    
    electricField[0] = electricField.back();
}

void JunctionPDE::calculateAvalancheProbabilities(const double& overbias, 
                                                  Vector<double>& electronProb, 
                                                  Vector<double>& holeProb, 
                                                  Vector<double>& probDepth) const 
{
    electronProb.clear();
    holeProb.clear();
    probDepth.clear();
    
    Vector<double> electricField;
    calculateElectricField(overbias, electricField, probDepth);
    calculateProbabilitiesFromElectricField(electricField, probDepth, dz*1e-4, electronProb, holeProb);
    Vector<double>::iterator it;
    
    for (it = probDepth.begin(); it != probDepth.end(); ++it) {
        *it = ((*it) - probDepth.back()) - topDepth;
    }    
}

void JunctionPDE::calculateDepletionZone(const double& overbias, 
                                         double& depStart, 
                                         double& depEnd) const 
{
    Vector<double> electronProb, holeProb, probDepth;
    calculateAvalancheProbabilities(overbias, electronProb, holeProb, probDepth);
    depStart = topDepth;
    depEnd = probDepth.back() - probDepth.front() + depStart;
}
