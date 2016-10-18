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
 * File        : spad_matrix_factory.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Feb 26 09:44:39 2016 -0500 by valentin
 * 
 * FILE_INFO_END */

#include "spad_matrix_factory.hh"

#include "spad_matrix.hh"
#include "spad_factory.hh"
#include "spad_configuration_factory.hh"
#include "coordinate.hh"
#include "string_cast.hh"
#include "var_type.hh"

SpadMatrixFactory::SpadMatrixFactory()
: ISensorMatrixFactory()
{}

SpadMatrixFactory::~SpadMatrixFactory()
{}

ISensorMatrix* SpadMatrixFactory::build(const Map<std::string, std::string>& matrixProperties, 
                                        const Map<std::string, std::string>& sensorProperties)
{
    if (!simulator) {
        throw std::logic_error("The ISimulator was not previously set. Call setSimulator before this call.");
    }
    if (!sensorFactory) {
        setSensorFactory(new SpadFactory());
    }
    if (!sensorConfigurationFactory) {
        SpadConfigurationFactory * temp = new SpadConfigurationFactory();
        temp->setSimulator(simulator);
        setSensorConfigurationFactory(temp);
    }
    SpadMatrix* matrix = new SpadMatrix();
    setProperties(matrix, matrixProperties);
    setSimulator(matrix);
    setSensorFactory(matrix);
    setSensorConfigurationFactory(matrix);
    matrix->initSensorConfiguration(sensorProperties);
    matrix->createSensors();
    return matrix;
}
