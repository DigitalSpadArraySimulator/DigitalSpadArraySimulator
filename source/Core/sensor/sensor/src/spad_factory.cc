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
 * File        : spad_factory.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */

#include "spad_factory.hh"

#include <math.h>

#include "charging_state.hh"
#include "config_pde.hh"
#include "electric_field_pde.hh"
#include "isensor_configuration.hh"
#include "junction_pde.hh"
#include "map.hh"
#include "polygon.hh"
#include "position.hh"
#include "quenching_state.hh"
#include "ready_state.hh"
#include "sipm.hh"
#include "spad.hh"
#include "spad_configuration.hh"
#include "string_cast.hh"
#include "var_type.hh"
#include "vector.hh"

SpadFactory::SpadFactory()
: SpadFactory(0)
{}

SpadFactory::SpadFactory(PDEBehavior* pde)
: ISensorFactory()
, model(0)
{}

SpadFactory::~SpadFactory()
{
    if (model) {
        delete model;
    }
}


void SpadFactory::setSensorConfiguration(ISensorConfiguration* sensorConfiguration)
{
    ISensorFactory::setSensorConfiguration(sensorConfiguration);
    
    createModel();
    calculateDepletionZone();
}

ISensor* SpadFactory::build(const Position2D& sensorCenter)
{
    if (!model || !sensorConfiguration) {
        throw std::logic_error("You must call SpadFactory::setSensorConfiguration before this call to set the parameters needed to create a Spad");
    }
    Spad* spad = new Spad();
    spad->polygon = new Polygon(*model, sensorCenter);
    spad->configuration = sensorConfiguration;
    return spad;
}

void SpadFactory::createModel()
{
    model = new Polygon(sensorConfiguration->getPropertyAs<int>(ISensorConfiguration::NB_VERTICES),
                        sensorConfiguration->getPropertyAs<double>(ISensorConfiguration::RADIUS_TO_VERTICES),
                        sensorConfiguration->getPropertyAs<double>(ISensorConfiguration::ANGLE),
                        Position2D(0.0, 0.0));
}

void SpadFactory::calculateDepletionZone()
{
    double overbias, depStart, depEnd;
    overbias = sensorConfiguration->getPropertyAs<double>(SpadConfiguration::OVERBIAS);
    
    sensorConfiguration->getPDE().calculateDepletionZone(overbias, depStart, depEnd);
    
    sensorConfiguration->setProperty(SpadConfiguration::SPAD_TOP_DEPTH, new VarType(depStart));
    sensorConfiguration->setProperty(SpadConfiguration::SPAD_DEP_DEPTH, new VarType(depEnd));
}
