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
 * File        : constant_absorption_coefficient.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 07:56:44 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef CONSTANT_ABSORPTION_COEFFICIENT_MATERIAL_H
#define CONSTANT_ABSORPTION_COEFFICIENT_MATERIAL_H

#include "absorption_behavior.hh"

/**
 * @brief An absorption behavior with the same coefficient for all wavelengths.
 */
class ConstantAbsorptionCoefficient : public AbsorptionBehavior {
private:
    ConstantAbsorptionCoefficient(const ConstantAbsorptionCoefficient&);
    ConstantAbsorptionCoefficient& operator=(ConstantAbsorptionCoefficient&);
    
    double coefficient;
public:
    /**
     * @brief Constructor.
     * 
     * @param coefficient The constant coefficient
     */
    ConstantAbsorptionCoefficient(const double& coefficient);
    
    /**
     * @brief Destructor.
     */
    virtual ~ConstantAbsorptionCoefficient() {}
    
    
    /**
     * @brief Get the absorption coefficient.
     * 
     * @return double The constant coefficient.
     */
    virtual inline double getAbsorptionCoefficient(const double&) const  override { return coefficient; }
};

#endif //CONSTANT_ABSORPTION_COEFFICIENT_MATERIAL_H