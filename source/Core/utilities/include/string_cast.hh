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
 * File        : string_cast.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 2 15:19:04 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef STRING_CAST_PROPERTIES_H
#define STRING_CAST_PROPERTIES_H

#include <string>

/// @brief Utilies function to cast a string

/**
 * @brief Cast a string into a type.
 * @param s The string to cast.
 * @param[out] out Will contain the data it the cast is successful.
 */
template <typename T>
void castTo(const std::string& s, T& out);

/**
 * @brief Cast a string into a double.
 * @param s The string to cast.
 * @param[out] out Will contain the double if the cast is successful.
 * @see http://www.cplusplus.com/reference/string/stod/
 */
template <>
void castTo(const std::string& s, double& out);

/**
 * @brief Cast a string into a int.
 * @param s The string to cast.
 * @param[out] out Will contain the int if the cast is successful.
 * @see http://www.cplusplus.com/reference/string/stoi/
 */
template <>
void castTo(const std::string& s, int& out);

/**
 * @brief Create a string from a value.
 * 
 * @param in The value.
 * @param s The string.
 */
template <typename T>
void castFrom(const T& in, std::string& s);

#include "string_cast.hpp"

#endif //STRING_CAST_PROPERTIES_H