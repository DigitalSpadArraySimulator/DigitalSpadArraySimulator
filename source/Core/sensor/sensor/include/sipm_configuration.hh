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
 * File        : sipm_configuration.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef SIPM_CONFIGURATION_H
#define SIPM_CONFIGURATION_H

#include "spad_configuration.hh"

class Sipm;
class SipmConfigurationFactory;

/**
 * @brief Derived IConfigurable containing every property mapping type and states for SIPM.
 */
class SipmConfiguration : public SpadConfiguration {
private:
    friend class Sipm;
    friend class SipmConfigurationFactory;
private:
    SipmConfiguration(const SipmConfiguration&);
    SipmConfiguration& operator=(const SipmConfiguration&);
    
protected:
    /**
     * @brief The total electric current used for a single simulation.
     */
    Vector<double> totalElectricCurrent;

    /**
     * @brief Update the total electric current.
     * 
     * @param electricCurrent The electric current used by the SiPM that triggered.
     * @param time The time when the first data occured.
     */
    void updateTotalElectricCurrent(const Vector<double>& electricCurrent, const double& time);
    
public:
    /**
     * @brief Constructor.
     */
    SipmConfiguration();
    
    /**
     * @brief Destructor.
     * 
     * @see SpadConfiguration::~SpadConfiguration
     */
    virtual ~SipmConfiguration() {}
    
    /**
     * @brief Reset the total electric current.
     */
    void resetTotalElectricCurrent();
    
    /**
     * @brief Get the total electric current.
     * 
     * @return const Vector< double >&
     */
    inline const Vector<double>& getTotalElectricCurrent() const {return totalElectricCurrent;}
    
public:
    /**
     * @brief (\f$\Omega\f$)
     * 
     * @warning for SiPM only.
     * 
     * PropertyName: "Rd"
     * 
     * PropertyType: double
     */
    static const std::string INTERNAL_RESISTANCE;
    
    /**
     * @brief Quenching time of an Avalanche. (ns)
     * 
     * @warning for SiPM only.
     * 
     * PropertyName: "AQT"
     * 
     * PropertyType: double
     */
    static const std::string AVALANCHE_QUENCHING_TIME;
    
    /**
     * @brief Jitter of the Quenching of an Avalanche. (FWHM ns)
     * 
     * @warning for SiPM only.
     * 
     * PropertyName: "AJT"
     * 
     * PropertyType: double
     */
    static const std::string AVALANCHE_JITTER;
};

#endif //SIPM_CONFIGURATION_H