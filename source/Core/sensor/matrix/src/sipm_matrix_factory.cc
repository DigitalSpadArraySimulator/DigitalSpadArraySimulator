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
 * File        : sipm_matrix_factory.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Apr 13 11:30:25 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "sipm_matrix_factory.hh"

#include "sipm_factory.hh"
#include "sipm_configuration_factory.hh"

SipmMatrixFactory::SipmMatrixFactory()
: SpadMatrixFactory()
{}

SipmMatrixFactory::~SipmMatrixFactory()
{}

ISensorMatrix* SipmMatrixFactory::build(const Map<std::string, std::string>& matrixProperties, 
                                        const Map<std::string, std::string>& sensorProperties)
{
    if (!simulator) {
        throw std::logic_error("The ISimulator was not previously set. Call setSimulator before this call.");
    }
    if (!sensorFactory) {
        setSensorFactory(new SipmFactory());
    }
    if (!sensorConfigurationFactory) {
        SipmConfigurationFactory * temp = new SipmConfigurationFactory();
        temp->setSimulator(simulator);
        setSensorConfigurationFactory(temp);
    }
    return SpadMatrixFactory::build(matrixProperties, sensorProperties);
}

