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
 * File        : iconfigurable_factory.hpp
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "iconfigurable.hh"
#include "log.hh"
#include "string_cast.hh"

template <typename T>
void IConfigurableFactory<T>::setProperties(IConfigurable* configurable, const Map<std::string, std::string>& properties)
{
    Map<std::string, std::string>::const_iterator it;
    VarType::SUPPORTED_TYPE type;
    std::string propertyName, propertyValue;
    int tempInt;
    double tempDouble;
    char tempChar;
    VarType* value;
    
    for (it = properties.begin(); it != properties.end(); ++it) {
        propertyName = it->first;
        propertyValue = it->second;
        type = configurable->getPropertyMappingType(propertyName);
        
        if (type == VarType::NONE) {
            LOG_STREAM(2) << "No mapping type was found for the property \"" << propertyName << "\". String will be used." << std::endl;
            type = VarType::STRING;
        }
        
        switch(type) {
            case VarType::ENUM:
            case VarType::INT:
                castTo(propertyValue, tempInt);
                value = new VarType(tempInt);
                break;
            case VarType::DOUBLE:
            case VarType::FLOAT:
                castTo(propertyValue, tempDouble);
                value = new VarType(tempDouble);
                break;
            case VarType::CHAR:
                tempChar = propertyValue[0];
                value = new VarType(tempChar);
                break;
            case VarType::STRING:
            default:
                value = new VarType(propertyValue);
                break;
        }
        configurable->setProperty(propertyName, value);
    }
}
