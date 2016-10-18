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
 * File        : isilicon.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 3 14:30:27 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef I_SILICON_H
#define I_SILICON_H

#include "iconfigurable.hh"

class AbsorptionBehavior;
class Photon;
class ISiliconFactory;

/**
 * @brief Derived IConfigurable containg all the properties for silicon material.
 */
class ISilicon : public IConfigurable {
private:
    friend class ISiliconFactory;
private:
    ISilicon(const ISilicon&);
    ISilicon& operator=(const ISilicon&);
    
protected:
    /**
     * @brief Constructor
     * 
     * Init all the properties mapping type.
     */
    ISilicon();
    
    /**
     * @brief The absorption behavior used for absorbing photons.
     * 
     * @see ISilicon::calculatePhotonAbsorptionPoint.
     */
    AbsorptionBehavior* absorptionBehavior;
    
public:
    /**
     * @brief The type of silicon available.
     */
    enum SiliconType {
        N_PWELL = 0, ///< n+ p- well
        P_NWELL = 1  ///< p+ n- well
    };
    
    /**
     * @brief Destructor.
     * 
     * @warning Will delete the absorption behavior.
     */
    virtual ~ISilicon();
    
    /**
     * @brief Calculate the absorption point of the photon in a sensor.
     * 
     * @param photon The photon
     */
    virtual void calculatePhotonAbsorptionPoint(Photon& photon);
    
public:
    /**
     * @brief The type of well.
     * 
     * PropertyName: "type"
     * 
     * PropertyType: Silicon::SiliconType
     */
    static const std::string DOPING_TYPE;
    
    /**
     * @brief A constant absorption coefficient (\f$cm^{-1}\f$). 
     * 
     * @warning Ignored if AbsorptionBehavior is already specified.
     * 
     * PropertyName: "alpha"
     * 
     * PropertyType: double
     */
    static const std::string ALPHA;
    
    /**
     * @brief (\f$cm^{-3}\f$).
     * 
     * PropertyName: "Nwell"
     * 
     * PropertyType: double
     */
    static const std::string WELL_DOPING;
    
    /**
     * @brief (\f$cm^{-3}\f$).
     * 
     * PropertyName: "Ntop"
     * 
     * PropertyType: double
     */
    static const std::string TOP_DOPING;
    
    /**
     * @brief (\f$cm^{-2}\f$).
     * 
     * PropertyName: "a"
     * 
     * PropertyType: double
     */
    static const std::string DOPING_GRADIENT;
    
    /**
     * @brief  Mobility of the electrons in the N zone (\f$\frac{m^2}{V*s}\f$).
     * 
     * PropertyName: "mun_N"
     * 
     * PropertyType: double
     */
    static const std::string N_ZONE_ELECTRON_MOBILITY;
    
    /**
     * @brief Mobility of the holes in the N zone (\f$\frac{m^2}{V*s}\f$).
     * 
     * PropertyName: "mup_N"
     * 
     * PropertyType: double
     */
    static const std::string N_ZONE_HOLE_MOBILITY;
    
    /**
     * @brief Mobility of the electrons in the P zone (\f$\frac{m^2}{V*s}\f$).
     * 
     * PropertyName: "mun_P"
     * 
     * PropertyType: double
     */
    static const std::string P_ZONE_ELECTRON_MOBILITY;
    
    /**
     * @brief Mobility of the holes in the P zone (\f$\frac{m^2}{V*s}\f$).
     * 
     * PropertyName: "mup_P"
     * 
     * PropertyType: double
     */
    static const std::string P_ZONE_HOLE_MOBILITY;
    
    /**
     * @brief (\f$cm^{-3}\f$). At the 300 Kelvin..
     * 
     * PropertyName: "ni"
     * 
     * PropertyType: double
     */
    static const std::string INTRINSIC_CARRIERS;
    
    /**
     * @brief Relative Permittivity of the silicon.
     * 
     * PropertyName: "Er"
     * 
     * PropertyType: double
     */
    static const std::string RELATIVE_PERMITTIVITY; 
    
    /**
     * @brief Relative mass of electrons for conductivity.
     * 
     * PropertyName: "mce"
     * 
     * PropertyType: double
     */
    static const std::string MASS_CONDUCTIVITY_ELECTRON;
    
    /**
     * @brief Relative mass of holes for conductivity.
     * 
     * PropertyName: "mch"
     * 
     * PropertyType: double
     */
    static const std::string MASS_CONDUCTIVITY_HOLE;
};

#endif //I_SILICON_H