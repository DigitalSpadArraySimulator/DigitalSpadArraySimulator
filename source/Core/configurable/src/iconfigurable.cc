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
 * File        : iconfigurable.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "iconfigurable.hh"

IConfigurable::IConfigurable()
: properties()
, propertiesMappingType()
{}

IConfigurable::~IConfigurable()
{
    resetProperties();
    resetPropertiesMappingType();
}

VarType* IConfigurable::getProperty(const std::string& propertyName) const
{
    Map<std::string, VarType*>::const_iterator it;
    VarType * property = 0;
    it = properties.find(propertyName);
    
    if (it != properties.end()) {
        property = it->second;
    }
    
    return property;
}

void IConfigurable::setProperty(const std::string& propertyName, VarType* propertyValue)
{
    VarType * property = getProperty(propertyName);
    
    if (property) {
        properties[propertyName] = propertyValue;
        delete property;
    } else {
        properties.insert(std::pair<std::string, VarType*>(propertyName, propertyValue));
    }
}

void IConfigurable::resetProperties()
{
    properties.clearAndDeleteValues();
}

VarType::SUPPORTED_TYPE IConfigurable::getPropertyMappingType(const std::string& propertyName) const
{
    Map<std::string, VarType::SUPPORTED_TYPE>::const_iterator it;
    VarType::SUPPORTED_TYPE type = VarType::NONE;
    it = propertiesMappingType.find(propertyName);
    
    if (it != propertiesMappingType.end()) {
        type = it->second;
    }
    
    return type;
}

void IConfigurable::setPropertyMappingType(const std::string& propertyName, const VarType::SUPPORTED_TYPE& type)
{
    VarType::SUPPORTED_TYPE mappingType = getPropertyMappingType(propertyName);
    
    if (mappingType != VarType::NONE) {
        propertiesMappingType[propertyName] = type;
    } else {
        propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(propertyName, type));
    }
}

void IConfigurable::resetPropertiesMappingType()
{
    propertiesMappingType.clear();
}
