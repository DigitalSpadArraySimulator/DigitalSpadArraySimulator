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
 * File        : isensor_matrix_factory.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "isensor_matrix_factory.hh"

#include <stdexcept>

#include "isensor_factory.hh"
#include "isensor_matrix.hh"
#include "isimulator.hh"

ISensorMatrixFactory::ISensorMatrixFactory()
: IConfigurableFactory< ISensorMatrix >()
, simulator(0)
, sensorFactory(0)
, sensorConfigurationFactory(0)
{}

ISensorMatrixFactory::~ISensorMatrixFactory()
{
    simulator = 0;
    sensorFactory = 0;
    sensorConfigurationFactory = 0;
}

void ISensorMatrixFactory::setSimulator(ISensorMatrix* sensorMatrix)
{
    sensorMatrix->simulator = simulator;
}

void ISensorMatrixFactory::setSensorFactory(ISensorMatrix* sensorMatrix)
{
    sensorMatrix->sensorFactory = sensorFactory;
}

void ISensorMatrixFactory::setSensorConfigurationFactory(ISensorMatrix* sensorMatrix)
{
    sensorMatrix->sensorConfigurationFactory = sensorConfigurationFactory;
}

void ISensorMatrixFactory::setSimulator(const ISimulator* simulator)
{
    if (!simulator) {
        throw std::invalid_argument("The given ISimulator is null");
    }
    this->simulator = simulator;
}

void ISensorMatrixFactory::setSensorFactory(ISensorFactory* sensorFactory)
{
    if (!sensorFactory) {
        throw std::invalid_argument("The given ISensorFactory is null");
    }
    if (this->sensorFactory != sensorFactory) {
        if (this->sensorFactory) {
            delete this->sensorFactory;
        }
        this->sensorFactory = sensorFactory;
    }
}

void ISensorMatrixFactory::setSensorConfigurationFactory(IConfigurableFactory<ISensorConfiguration>* sensorConfigurationFactory)
{
    if (!sensorConfigurationFactory) {
        throw std::invalid_argument("The given ISensorFactory is null");
    }
    if (this->sensorConfigurationFactory != sensorConfigurationFactory) {
        if (this->sensorConfigurationFactory) {
            delete this->sensorConfigurationFactory;
        }
        this->sensorConfigurationFactory = sensorConfigurationFactory;
    }
}

ISensorMatrix* ISensorMatrixFactory::build(const Map<std::string, std::string>& properties)
{
    return build(properties, Map<std::string, std::string>());
}
