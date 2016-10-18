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
 * File        : iconfigurable_factory.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef I_CONFIGURABLE_FACTORY_H
#define I_CONFIGURABLE_FACTORY_H

#include "map.hh"

class IConfigurable;

/**
 * @brief Abstract class that can be used to build a configurable object.
 * 
 * @warning This class was intended to create IConfigurable object. Please specialize this class with a derived IConfigurable type while inheriting this class.
 */
template <typename T>
class IConfigurableFactory {
private:
    IConfigurableFactory(const IConfigurableFactory&);
    IConfigurableFactory& operator=(const IConfigurableFactory&);
    
protected:
    /**
     * @brief Constructor.
     */
    IConfigurableFactory() {}
    
    /**
     * @brief Set the properties of an configurable according to it's own properties mapping type.
     * 
     * This function should be called by derived class in the build function.
     * 
     * @param configurable The object to configure.
     * @param properties The properties to set.
     */
    virtual void setProperties(IConfigurable* configurable, const Map<std::string, std::string>& properties);
    
public:
    /**
     * @brief Destructor.
     */
    virtual ~IConfigurableFactory() {}
    
    /**
     * @brief Build an object with certain properties.
     * 
     * @param properties The properties to set to the configurable object.
     * @return T* The created configurable object.
     */
    virtual T* build(const Map<std::string, std::string>& properties) = 0;
};

#include "iconfigurable_factory.hpp"

#endif //I_CONFIGURABLE_FACTORY_H