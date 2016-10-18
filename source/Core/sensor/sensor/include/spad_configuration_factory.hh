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
 * File        : spad_configuration_factory.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef SPAD_CONFIGURATION_FACTORY_H
#define SPAD_CONFIGURATION_FACTORY_H

#include "iconfigurable_factory.hh"

class ISensorConfiguration;
class SpadConfiguration;
class PDEBehavior;
class ISimulator;

/**
 * @brief Derived IConfigurableFactory specialized for creating SpadConfiguration.
 */
class SpadConfigurationFactory : public IConfigurableFactory<ISensorConfiguration> {
private:
    SpadConfigurationFactory(const SpadConfigurationFactory&);
    SpadConfigurationFactory& operator=(const SpadConfigurationFactory&);
protected:
    /**
     * @brief The pde behavior that will be shared by all sensors in a matrix through the configuration.
     */
    PDEBehavior * pde;
    
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    /**
     * @brief A reference to the simulator that will be shared by all sensors in a matrix through the configuration.
     */
    ISimulator const * simulator;
#endif //DOXYGEN_SHOULD_SKIP_THIS
    
    /**
     * @brief This function will be called if the pde behavior is not already set when build will be called.
     * 
     * The pde will be a ConfigPDE if the properties SpadConfiguration::PDE_A and SpadConfiguration::PDE_B are presents.
     * 
     * The pde will be a JunctionPDE otherwise.
     * 
     * @param spadConfig The configuration.
     * @see IConfigurableFactory::build.
     */
    void detectPDE(SpadConfiguration* spadConfig);
    
    /**
     * @brief Create a ConfigPDE that will be used by all sensors in a matrix through the configuration.
     * 
     * @param spadConfig The configuration.
     * @param pdeA
     * @param pdeB
     * @see ConfigPDE
     */
    void createConfigPDE(SpadConfiguration* spadConfig, const double& pdeA, const double& pdeB);
    
    /**
     * @brief Create a JunctionPDE that will be used by all sensors in a matrix through the configuration.
     * 
     * @param spadConfig The configuration.
     */
    void createJunctionPDE(SpadConfiguration* spadConfig);
    
    /**
     * @brief Create the probabilities information when the sensor is in ready state.
     * 
     * @warning The pde behavior must be set before this call.
     * 
     * @param spadConfig The configuration.
     */
    void createReadySpadInfo(SpadConfiguration* spadConfig);
    
public:
    /**
     * @brief Default constructor.
     */
    SpadConfigurationFactory();
    
    /**
     * @brief Constructor with a specific pde behavior.
     * 
     * @param pde The pde behavior.
     */
    SpadConfigurationFactory(PDEBehavior * pde);
    
    /**
     * @brief Destructor.
     * 
     * @warning Will not delete the pde behavior.
     */
    virtual ~SpadConfigurationFactory();
    
    /**
     * @brief Set the simulator that will be used when creating the configuration.
     * 
     * @param simulator The simulator.
     */
    virtual void setSimulator(ISimulator const * simulator);
    
    /**
     * @brief Create a configuration based on the given properties.
     * 
     * @warning The function SpadConfigurationFactory::setSimulator must be called before this call.
     * 
     * @param properties The properties.
     * @return ISensorConfiguration*
     */
    virtual ISensorConfiguration* build(const Map<std::string, std::string>& properties) override;
};

#endif //SPAD_CONFIGURATION_FACTORY_H