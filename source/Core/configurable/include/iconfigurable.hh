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
 * File        : iconfigurable.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef I_CONFIGURABLE_H
#define I_CONFIGURABLE_H

#include <string>

#include "map.hh"
#include "var_type.hh"

/**
 * @brief Abstract class that represents an object that can be configured.
 */
class IConfigurable{
private:
    IConfigurable(const IConfigurable&);
    IConfigurable& operator=(const IConfigurable&);
    
protected:
    /**
     * @brief Constructor.
     */
    IConfigurable();
    
    /**
     * @brief Destructor.
     * 
     * @warning Will delete all the VarType in the properties map.
     */
    virtual ~IConfigurable();
    
    /**
     * @brief A Map <PropertyName, PropertyValue>
     */
    Map<std::string, VarType*> properties;
    
    /**
     * @brief A Map <PropertyName, PropertyType>
     */
    Map<std::string, VarType::SUPPORTED_TYPE> propertiesMappingType;

public:
    /**
     * @brief Get a property value.
     * 
     * @param propertyName The property name.
     * @return VarType*
     */
    virtual VarType* getProperty(const std::string& propertyName) const;
    
    /**
     * @brief Set a property.
     * 
     * @warning If the property already exists, the old one will be overwritten and the old VarType will be deleted.
     * 
     * @param propertyName The property name.
     * @param propertyValue The property value.
     */
    virtual void setProperty(const std::string& propertyName, VarType* propertyValue);
    
    /**
     * @brief Reset the properties Map.
     * 
     * @warning All the VarType will be deleted.
     */
    virtual void resetProperties();
    
    /**
     * @brief Get a property and cast the VarType.
     * 
     * @param propertyName The property name.
     * @return T
     */
    template <typename T>
    T getPropertyAs(const std::string& propertyName) const;
    
    /**
     * @brief Get the property type.
     * 
     * @warning If the property type is not found, VarType::SUPPORTED_TYPE::NONE will be returned.
     * 
     * @param propertyName The property name.
     * @return VarType::SUPPORTED_TYPE
     */
    virtual VarType::SUPPORTED_TYPE getPropertyMappingType(const std::string& propertyName) const;
    
    /**
     * @brief Set the property type.
     * 
     * @warning If the property mapping type already exists, the old one will be overwritten.
     * 
     * @param propertyName The property name.
     * @param type The property type.
     */
    virtual void setPropertyMappingType(const std::string& propertyName, const VarType::SUPPORTED_TYPE& type);
    
    /**
     * @brief Reset the properties mapping type Map.
     */
    virtual void resetPropertiesMappingType();
};

#include "iconfigurable.hpp"

#endif //I_CONFIGURABLE_H