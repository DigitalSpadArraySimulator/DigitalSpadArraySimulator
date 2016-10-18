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
 * File        : sipm_configuration_factory.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "sipm_configuration_factory.hh"
#include "sipm_configuration.hh"

SipmConfigurationFactory::SipmConfigurationFactory()
: SpadConfigurationFactory()
{}

SipmConfigurationFactory::SipmConfigurationFactory(PDEBehavior* pde)
: SpadConfigurationFactory(pde)
{}

SipmConfigurationFactory::~SipmConfigurationFactory()
{}

ISensorConfiguration* SipmConfigurationFactory::build(const Map<std::string, std::string>& properties)
{
    SipmConfiguration* sipmConfig = new SipmConfiguration();
    setProperties(sipmConfig, properties);
    sipmConfig->simulator = simulator;
    if (!pde) {
        detectPDE(sipmConfig);
    } else {
        createReadySpadInfo(sipmConfig);
    }
    sipmConfig->pde = pde;
    return sipmConfig;
}
