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
 * File        : stochastic.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 9 15:09:28 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef STOCHASTIC_UTILITIES_H
#define STOCHASTIC_UTILITIES_H

#include "vector.hh"

/**
 * @brief According to rate and time interval, returns a list times at which events have started
 * 
 * @param rate Use for the exponential random rate (\f$\lambda\f$).
 * @param timeMax Time to stop.
 * @param timeMin Time to start.
 * @param nbProcess Number of times to generate at each iteration.
 * @param[out] times The generated times.
 */
void poissonBirth(const double& rate, const double& timeMax, const double& timeMin, const double& nbProcess, Vector<Vector<double>>& times);

#endif //STOCHASTIC_UTILITIES_H