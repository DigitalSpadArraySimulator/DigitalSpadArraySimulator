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
 * File        : silicon_factory.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 3 14:30:27 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef SILICON_FACTORY_MATERIAL_H
#define SILICON_FACTORY_MATERIAL_H

#include <string>

#include "map.hh"
#include "vector.hh"

#include "isilicon_factory.hh"

class AbsorptionBehavior;

/**
 * @class SiliconFactory
 * @brief Static class to configure the Silicon used in the SpadMatrix.
 */
class SiliconFactory : public ISiliconFactory {
private:
    SiliconFactory(const SiliconFactory&);
    SiliconFactory& operator=(const SiliconFactory&);
    
    AbsorptionBehavior* absorptionBehavior;
    
public:
    /**
     * @brief Constructor.
     */
    SiliconFactory();
    
    /**
     * @brief Constructor.
     * 
     * A ConstantAbsorptionCoefficient will be created as AbsorptionBehavior.
     * 
     * @param coefficients The constant coefficient.
     */
    SiliconFactory(const double& coefficients);
    
    /**
     * @brief Constructor.
     * 
     * A SiliconOpticalProperties will be created as AbsorptionBehavior.
     * 
     * @param wavelengths The wavelengths.
     * @param coefficients The coefficients.
     */
    SiliconFactory(const Vector<double>& wavelengths, const Vector<double>& coefficients);
    
    /**
     * @brief Destructor.
     * 
     * @warning Will not delete the absorption behavior.
     */
    ~SiliconFactory();
    
    /**
     * @brief Build a silicon material.
     * 
     * @warning If the default constructor was called, the properties ISilicon::ALPHA is mandatory.
     * 
     * @param properties The silicon properties.
     * @return ISilicon*
     */
    virtual ISilicon* build(const Map<std::string, std::string>& properties)  override;
};

#endif //SILICON_FACTORY_MATERIAL_H