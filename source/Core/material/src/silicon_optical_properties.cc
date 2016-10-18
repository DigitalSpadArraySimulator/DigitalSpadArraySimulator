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
 * File        : silicon_optical_properties.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 07:56:44 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include <stdexcept>
#include "silicon_optical_properties.hh"
#include "array_algorithm.hh"

SiliconOpticalProperties::SiliconOpticalProperties(const Vector< double >& wavelengths, const Vector< double >& coefficients)
: wavelengths(wavelengths)
, coefficients(coefficients)
{
    if (wavelengths.size() != coefficients.size() || wavelengths.size() == 0) {
        throw std::invalid_argument("");
    }
}

SiliconOpticalProperties::~SiliconOpticalProperties()
{
    wavelengths.clear();
    coefficients.clear();
}

double SiliconOpticalProperties::getAbsorptionCoefficient(const double& wavelength) const
{
    int index = Dichotomic::findSmallerClosestIndex(wavelengths, wavelength);
    if (index == -1) {
        throw std::out_of_range("OpticalProperties were not initialized");
    }
    return coefficients[index];
}
