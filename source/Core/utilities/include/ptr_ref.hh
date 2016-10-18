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
 * File        : ptr_ref.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Feb 25 11:38:37 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef PTR_REF_UTILITIES_H
#define PTR_REF_UTILITIES_H

/// @brief Those function allow the user to retrieve a reference or a pointer of a Template without having to care if T is a pointer or a reference

/**
 * @brief Return a reference on the object when T is a reference to the object
 * @param obj The object
 * @return T& The reference of the object
 */
template<typename T>
T& ref(T& obj) {return obj;}

/**
 * @brief Return a const reference on the object when T is a const reference to the object
 * @param obj The object
 * @return T& The reference of the object
 */
template<typename T>
const T& ref(const T& obj) {return obj;}

/**
 * @brief Return a reference on the object when T is a pointer to the object
 * @param obj a pointer to the object
 * @return T& The reference of the object
 */
template<typename T>
T& ref(T* obj) {return *obj;}

/**
 * @brief Return a pointer on the object when T is a reference to the object
 * @param obj The object
 * @return T* A pointer to the object
 * @see http://stackoverflow.com/a/14466705
 */
template<typename T>
T * ptr(T& obj) {return &obj;}

/**
 * @brief Return a pointer on the object when T is a pointer to the object
 * @param obj A pointer to the object
 * @return T* A pointer to the object
 * @see http://stackoverflow.com/a/14466705
 */
template<typename T>
T * ptr(T* obj) {return obj;}

#endif //PTR_REF_UTILITIES_H