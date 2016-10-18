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
 * File        : sipm_configuration_factory.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef SIPM_CONFIGURATION_FACTORY_H
#define SIPM_CONFIGURATION_FACTORY_H

#include "spad_configuration_factory.hh"

/**
 * @brief IConfigurableFactory specialized in creating ISensorConfiguration for sipm.
 */
class SipmConfigurationFactory : public SpadConfigurationFactory {
private:
    SipmConfigurationFactory(const SipmConfigurationFactory&);
    SipmConfigurationFactory& operator=(const SipmConfigurationFactory&);
    
public:
    /**
     * @brief Constructor.
     */
    SipmConfigurationFactory();
    
    /**
     * @brief Constructor with a specific pde behavior.
     * 
     * @param pde The pde behavior.
     */
    SipmConfigurationFactory(PDEBehavior * pde);
    
    /**
     * @brief Destructor.
     */
    virtual ~SipmConfigurationFactory();
    
    /**
     * @brief Build a configuration for SIPM.
     * 
     * @param properties The properties.
     * @return ISensorConfiguration* The configuration that was built.
     */
    virtual ISensorConfiguration* build(const Map<std::string, std::string>& properties) override;
};

#endif //SIPM_CONFIGURATION_FACTORY_H