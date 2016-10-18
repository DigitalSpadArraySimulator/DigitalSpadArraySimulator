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
 * File        : spad_configuration.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef SPAD_CONFIGURATION_H
#define SPAD_CONFIGURATION_H

#include "isensor_configuration.hh"

/**
 * @brief Derived ISensorConfiguration containing the properties required for a spad.
 */
class SpadConfiguration : public ISensorConfiguration {
private:
    friend class SpadConfigurationFactory;
private:
    SpadConfiguration(const SpadConfiguration&);
    SpadConfiguration& operator=(const SpadConfiguration&);

public:
    /**
     * @brief Init the properties mapping type.
     */
    SpadConfiguration();
    /**
     * @brief Destructor.
     * 
     * @see ISensorConfiguration::~ISensorConfiguration
     */
    virtual ~SpadConfiguration() {}
    
public:
    /**
     * @brief (V)
     * 
     * PropertyName: "Vbreak"
     * 
     * PropertyType: double
     */
    static const std::string BREAKDOWN_TENSION;
    
    /**
     * @brief (V)
     * 
     * PropertyName: "Overbias"
     * 
     * PropertyType: double
     */
    static const std::string OVERBIAS;
    
    /**
     * @brief Avalanche propagation delay \f$5*\tau\f$. (ns)
     * 
     * PropertyName: "SPADdelay"
     * 
     * PropertyType: double
     */
    static const std::string SPAD_DELAY;
    
    /**
     * @brief Avalanche propagation jitter. (FWHM ns)
     * 
     * PropertyName: "SPADjitter"
     * 
     * PropertyType: double
     */
    static const std::string SPAD_JITTER;
    
    /**
     * @brief Thermical noise. (\f$\frac{\text{count}/\text{s}}{\mu\text{m}^2}\f$)
     * 
     * PropertyName: "DCRrate"
     * 
     * PropertyType: double
     */
    static const std::string DCR_RATE;
    
    /**
     * @brief Crosstalk probability between adjacent Spad.
     * 
     * @warning Value must be between 0 and 1.
     * 
     * PropertyName: "Crosstalk"
     * 
     * PropertyType: double
     */
    static const std::string CROSSTALK_PROB;
    
    /**
     * @brief Afterpulsing probability after an avalanche occured.
     * 
     * @warning Value must be between 0 and 1.
     * 
     * PropertyName: "AP_prob"
     * 
     * PropertyType: double
     */
    static const std::string AFTERPULSING_PROB;
    
    /**
     * @brief Delay before the aftepulse manifest itself. (ns)
     * 
     * PropertyName: "AP_delay"
     * 
     * PropertyType: double
     */
    static const std::string AFTERPULSING_DELAY;
    
    /**
     * @brief (kelvin)
     * 
     * PropertyName: "T"
     * 
     * PropertyType: double
     */
    static const std::string TEMPERATURE;
    
    /**
     * @brief Depth of the zone doped ++. (\f$\mu\text{m}\f$)
     * 
     * PropertyName: "spadtop"
     * 
     * PropertyType: double
     */
    static const std::string SPAD_TOP_DEPTH;
    
    /**
     * @brief Total depth of the Spad. (\f$\mu\text{m}\f$)
     * 
     * PropertyName: "spadwell"
     * 
     * PropertyType: double
     */
    static const std::string SPAD_WELL_DEPTH;
    
    /**
     * @brief Used for using a specific PDE to the Spad.
     * 
     * \f[pde=A*(1-e^{-B*\text{overbias}})\f]
     * 
     * @see ConfigPDE
     * 
     * PropertyName: "PDE_A"
     * 
     * PropertyType: double
     */
    static const std::string PDE_A;
    
    /**
     * @brief Used for using a specific PDE to the Spad.
     * 
     * \f[pde=A*(1-e^{-B*\text{overbias}})\f]
     * 
     * @see ConfigPDE
     * 
     * PropertyName: "PDE_B"
     * 
     * PropertyType: double
     */
    static const std::string PDE_B;
    
    /**
     * @brief The depth were the DepletionZone ends. (\f$\mu\text{m}\f$)
     * 
     * @warning This property is calculated by the PDEBehavior.
     * 
     * PropertyName: "spaddep"
     * 
     * PropertyType: double
     */
    static const std::string SPAD_DEP_DEPTH;
};

#endif //SPAD_CONFIGURATION_H