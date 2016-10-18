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
 * File        : constants.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 16:57:33 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef CONSTANTS_PHYSICS_H
#define CONSTANTS_PHYSICS_H

#include "map.hh"
#include <string>

class VarType;

/**
 * @brief Static class that contains some physical constants.
 */
class PhysicsConstants{
private:
    static Map<std::string, double> constants;
    
public:
    
    /**
     * ConstantName : "q" \f$(C)\f$
     * 
     * ConstantValue : 1.6E-019
     */
    static const std::string ELECTRON_CHARGE;
    
    /**
     * ConstantName : "k" \f$(\text{eV}*\text{K}^{-1})\f$
     * 
     * ConstantValue : 0.00008617
     */
    static const std::string BOLTZMANN_CONSTANT;
    
    /**
     * ConstantName : "k_JK" \f$(\text{J}*\text{K}^{-1})\f$
     * 
     * ConstantValue : 1.38E-023
     */
    static const std::string BOLTZMANN_CONSTANT_J;
    
    /**
     * ConstantName : "E0" \f$(\text{F}/\text{cm})\f$
     * 
     * ConstantValue : 8.85E-14
     */
    static const std::string VOID_PERMITTIVITY;
    
    /**
     * ConstantName : "m0" \f$(\text{kg})\f$
     * 
     * ConstantValue : 9.11E-031
     */
    static const std::string ELECTRON_REST_MASS;
    
    /**
     * ConstantName : "hc" \f$(\text{eV}*\mu\text{m})\f$
     * 
     * ConstantValue : 1.23984193
     */
    static const std::string PlANCK_SPEED_LIGHT;
    
    /**
     * @brief Initialize only the default constants with their default value.
     */
    static void init();
    
    /**
     * @brief Initialize the default constants with their default value, then add the given constants (overwrite if needed).
     * 
     * @param constants The new constants or constants new value.
     */
    static void init(const Map<std::string, std::string>& constants);
    
    /**
     * @brief Remove every constants.
     */
    static void reset();
    
    /**
     * @brief Get a constant value.
     * 
     * @warning This class must have been Initialize at least once before use.
     * 
     * @param constant The constant's name.
     * @return double
     */
    static double get(const std::string& constant);
};

#endif //CONSTANTS_PHYSICS_H