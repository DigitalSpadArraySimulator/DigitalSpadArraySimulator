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
 * File        : var_type.hpp
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 2 15:19:04 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include <cstdlib>
#include <cstring>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include "ptr_ref.hh"

template<typename T> 
VarType::VarType(const T& value)
{
    this->dataSize =  sizeof(ref(value));
    this->data = malloc(this->dataSize);
    memcpy(this->data, (void*) ptr(value), this->dataSize);
}

template<typename T>
void VarType::getAs(T& output) const
{
    if (sizeof(ref(output)) != this->dataSize) {
        throw std::bad_cast();
    }
    memcpy((void*) ptr(output), this->data, this->dataSize);
}

template<typename T>
T VarType::getAs() const
{
    T temp;
    getAs(temp);
    return temp;
}

template<typename T> 
void VarType::operator=(const T& value)
{
    free(this->data);
    this->dataSize =  sizeof(ref(value));
    this->data = malloc(this->dataSize);
    memcpy(this->data, (void*) ptr(value), this->dataSize);
}
