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
 * File        : var_type.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 2 15:19:04 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef VAR_TYPE_UTILITIES_H
#define VAR_TYPE_UTILITIES_H

// This code is inspired from boost/any.hpp
#include <cstddef>
#include <string>

/**
 * @brief Container class able to contain any simple data.
 */
class VarType {
private:
    VarType();
    VarType(const VarType&);
    VarType& operator=(const VarType&);
    
public:
    /**
     * @brief The different supported type by VarType
     */
    enum SUPPORTED_TYPE {
        NONE = -1,      ///< Not a valid type.
        ENUM = 0,       ///< An enum (stored internally as int).
        CHAR = 1,       ///< A single char.
        INT = 2,        ///< A int.
        FLOAT = 3,      ///< A float (stored internally as double).
        DOUBLE = 4,     ///< A double,
        STRING = 5      ///< A string (stored internally as an array of char).
    };
    
    /**
     * @brief Create a VarType container from a variable.
     * @param value The variable to wrap.
     */
    template<typename T> 
    VarType(const T& value);
    
    /**
     * @brief Assigne a new variable to this container.
     * @warning Variable previously wrapped will be deleted.
     * @param value The variable to wrap.
     */
    template<typename T> 
    void operator=(const T& value);
    
    /**
     * @brief Free the memory alocated by the container.
     */
    ~VarType();
    
    /**
     * @brief Return a reference to the wrapped variable.
     * @param[out] output
     */
    template<typename T>
    void getAs(T& output) const;
    
    /**
     * @brief Return a copy of the wrapped variable.
     * @return T A copy of the wrapped variable.
     */
    template<typename T>
    T getAs() const;
    
private:
    void* data;
    std::size_t dataSize;
};

#include "var_type.hpp"

#endif //VARTTYPE_UTILITIES_H