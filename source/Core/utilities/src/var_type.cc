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
 * File        : var_type.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 2 15:19:04 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "var_type.hh"
#include <cstdlib>

VarType::~VarType()
{
    free(this->data);
}

/**
 * @brief Constructor specialization with string.
 * 
 * @param value A string.
 */
template<> 
VarType::VarType(const std::string& value)
{
    this->dataSize = value.size();
    this->data = malloc(this->dataSize);
    memcpy(this->data, (void*)value.c_str(), this->dataSize);
}

/**
 * @brief getAs specialization with string.
 * 
 * @param output A string.
 */
template<>
void VarType::getAs(std::string& output) const
{
    output.assign((const char*) this->data, this->dataSize);
}
