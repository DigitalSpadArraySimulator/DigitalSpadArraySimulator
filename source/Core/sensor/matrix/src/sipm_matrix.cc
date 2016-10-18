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
 * File        : sipm_matrix.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Apr 13 11:30:25 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "sipm_matrix.hh"
#include "sipm_configuration.hh"

SipmMatrix::SipmMatrix()
: SpadMatrix()
{}

SipmMatrix::~SipmMatrix()
{}

void SipmMatrix::reset()
{
    ISensorMatrix::reset();
    
    dynamic_cast<SipmConfiguration*>(sensorConfiguration)->resetTotalElectricCurrent();
}

