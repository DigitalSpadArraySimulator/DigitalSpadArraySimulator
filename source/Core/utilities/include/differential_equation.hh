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
 * File        : differential_equation.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 16:57:33 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef DIFFERENTIAL_EQUATION_H
#define DIFFERENTIAL_EQUATION_H

#include "vector.hh"

/**
 * @brief Calculate probabilities of Electron and Hole to cause an avalanche base on depth reached
 * 
 * This function translates the electric field in a ionization rate profile
 * f or pn junctions in silicon, then uses those ioniza*tion
 * Parameters and equatioon obtained from Grant via Thornber vis Sze
 * "Application of scaling to problems in high-field electronic transport"
 * K.K. thornber, Bell laboratories, Murray Hill, 1980
 * 
 * @param electricField The electric field value based on the depth
 * @param z The depths
 * @param dz The depths interval
 * @param[out] probElectron The probabilities of an electron to cause an avalanche based on the depth
 * @param[out] probHole The probabilities of an hole to cause an avalanche based on the depth
 */
void calculateProbabilitiesFromElectricField(const Vector<double>& electricField,
                                             const Vector<double>& z,
                                             const double& dz,
                                             Vector<double>& probElectron,
                                             Vector<double>& probHole);

#endif //DIFFERENTIAL_EQUATION_H