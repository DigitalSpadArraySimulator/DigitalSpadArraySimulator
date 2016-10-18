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
 * File        : silicon_factory.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 3 14:30:27 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "absorption_behavior.hh"
#include "constant_absorption_coefficient.hh"
#include "silicon.hh"
#include "silicon_factory.hh"
#include "silicon_optical_properties.hh"
#include "string_cast.hh"
#include "var_type.hh"


SiliconFactory::SiliconFactory()
: absorptionBehavior(0)
{}

SiliconFactory::SiliconFactory(const double& coefficients)
: absorptionBehavior(new ConstantAbsorptionCoefficient(coefficients))
{}

SiliconFactory::SiliconFactory(const Vector<double>& wavelengths, const Vector<double>& coefficients)
: absorptionBehavior(new SiliconOpticalProperties(wavelengths, coefficients))
{}

SiliconFactory::~SiliconFactory()
{}

ISilicon* SiliconFactory::build(const Map<std::string, std::string>& properties)
{
    ISilicon* silicon = new Silicon();
    this->setProperties(silicon, properties);
    if (!absorptionBehavior) {
        absorptionBehavior = new ConstantAbsorptionCoefficient(silicon->getPropertyAs<double>(ISilicon::ALPHA) / 10000);
    }
    this->setAbsorptionBehavior(silicon, absorptionBehavior);
    return silicon;
}
