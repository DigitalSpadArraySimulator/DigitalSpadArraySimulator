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
 * File        : silicon_optical_properties.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 07:56:44 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef SILICON_OPTICAL_PROPERTIES_MATERIAL_H
#define SILICON_OPTICAL_PROPERTIES_MATERIAL_H

#include "absorption_behavior.hh"
#include "vector.hh"

/**
 * @brief Derived AbsorptionBehavior based on the photon wavelengths.
 */
class SiliconOpticalProperties : public AbsorptionBehavior{
private:
    SiliconOpticalProperties();
    SiliconOpticalProperties(const SiliconOpticalProperties&);
    SiliconOpticalProperties& operator=(const SiliconOpticalProperties&);
    
    Vector<double> wavelengths;
    Vector<double> coefficients;
public:
    /**
     * @brief Constructor.
     * 
     * @warning The wavelengths should be sorted by the smallest to to biggest and under the same unit.
     * 
     * @param wavelengths The wavelengths.
     * @param coefficients The coefficients associated to the wavelengths.
     */
    SiliconOpticalProperties(const Vector<double>& wavelengths, const Vector<double>& coefficients);
    
    /**
     * @brief Destructor.
     */
    virtual ~SiliconOpticalProperties();
    
    /**
     * @brief Get the absorption coefficient associated with the smallest closest wavelengths.
     * 
     * @param wavelength The wavelength.
     * @return double The coefficient associated with the closest.
     */
    virtual double getAbsorptionCoefficient(const double& wavelength) const  override;
};

#endif //SILICON_OPTICAL_PROPERTIES_MATERIAL_H