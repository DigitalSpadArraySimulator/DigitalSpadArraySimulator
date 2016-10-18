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
 * File        : absorption_behavior.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 07:56:44 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef ABSORPTION_BEHAVIOR_MATERIAL_H
#define ABSORPTION_BEHAVIOR_MATERIAL_H

/**
 * @brief Abstract class that describes how to get an Absorption Coefficient based on a wavelength.
 */
class AbsorptionBehavior{
private:
    AbsorptionBehavior(const AbsorptionBehavior&);
    AbsorptionBehavior& operator=(AbsorptionBehavior&);
    
protected:
    /**
     * @brief Default Constructor.
     */
    AbsorptionBehavior() {}
    
public:
    /**
     * @brief Destructor.
     */
    virtual ~AbsorptionBehavior(){}
    
    /**
     * @brief Get an absorption coefficient based on a wavelength.
     * 
     * @param wavelength The wavelength.
     * @return double
     */
    virtual double getAbsorptionCoefficient(const double& wavelength) const = 0;
};

#endif //ABSORPTION_BEHAVIOR_MATERIAL_H