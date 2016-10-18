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
 * File        : igenerator.hpp
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Apr 7 14:43:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include <stdexcept>

//#include "isimulator.hh"

template <typename T>
IGenerator<T>::IGenerator(ISimulator const * simulator) 
: simulator(simulator)
{
    if (!simulator) {
        throw std::invalid_argument("The given ISimulator is null.");
    }
}

template <typename T>
IGenerator<T>::~IGenerator() 
{
    simulator = 0;
}
