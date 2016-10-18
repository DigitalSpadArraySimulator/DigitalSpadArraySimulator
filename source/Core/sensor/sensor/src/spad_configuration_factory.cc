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
 * File        : spad_configuration_factory.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "spad_configuration_factory.hh"

#include "isensor_configuration.hh"
#include "spad_configuration.hh"
#include "pde_behavior.hh"
#include "config_pde.hh"
#include "junction_pde.hh"
#include <isimulator.hh>

SpadConfigurationFactory::SpadConfigurationFactory()
: SpadConfigurationFactory(0)
{}

SpadConfigurationFactory::SpadConfigurationFactory(PDEBehavior* pde)
: IConfigurableFactory<ISensorConfiguration>()
, pde(pde)
{}

SpadConfigurationFactory::~SpadConfigurationFactory()
{
    pde = 0; // Will be delete by the ISensorConfiguration
    simulator = 0;
}

void SpadConfigurationFactory::setSimulator(const ISimulator* simulator)
{
    if (!simulator) {
        throw std::invalid_argument("The given ISimulator is null");
    }
    this->simulator = simulator;
}

ISensorConfiguration* SpadConfigurationFactory::build(const Map<std::string, std::string>& properties)
{
    SpadConfiguration* spadConfig = new SpadConfiguration();
    setProperties(spadConfig, properties);
    spadConfig->simulator = simulator;
    if (!pde) {
        detectPDE(spadConfig);
    } else {
        createReadySpadInfo(spadConfig);
    }
    spadConfig->pde = pde;
    return spadConfig;
}

void SpadConfigurationFactory::detectPDE(SpadConfiguration* spadConfig)
{
    double pdeA, pdeB;
    VarType *vA, *vB;
    vA = spadConfig->getProperty(SpadConfiguration::PDE_A);
    vB = spadConfig->getProperty(SpadConfiguration::PDE_B);
    if (vA && (pdeA = vA->getAs<double>()) != 0 &&
        vB && (pdeB = vB->getAs<double>()) != 0) {
        createConfigPDE(spadConfig, pdeA, pdeB);
    } else {
        createJunctionPDE(spadConfig);
    }
}

void SpadConfigurationFactory::createConfigPDE(SpadConfiguration* spadConfig, const double& pdeA, const double& pdeB)
{
    double spadDepth = spadConfig->getPropertyAs<double>(SpadConfiguration::SPAD_WELL_DEPTH);
    pde = new ConfigPDE(pdeA, pdeB, spadDepth);
    createReadySpadInfo(spadConfig);
}

void SpadConfigurationFactory::createJunctionPDE(SpadConfiguration* spadConfig)
{
    double temperature = spadConfig->getPropertyAs<double>(SpadConfiguration::TEMPERATURE);
    double breakdown = spadConfig->getPropertyAs<double>(SpadConfiguration::BREAKDOWN_TENSION);
    double spadTop = spadConfig->getPropertyAs<double>(SpadConfiguration::SPAD_TOP_DEPTH);
    pde = new JunctionPDE(spadConfig->getSimulator()->getSilicon(), temperature, breakdown, spadTop);
    createReadySpadInfo(spadConfig);
}

void SpadConfigurationFactory::createReadySpadInfo(SpadConfiguration* spadConfig)
{
    pde->calculateAvalancheProbabilities(
        spadConfig->getPropertyAs<double>(SpadConfiguration::OVERBIAS),
        spadConfig->readyProbE,
        spadConfig->readyProbH,
        spadConfig->readyDepths
    );
}