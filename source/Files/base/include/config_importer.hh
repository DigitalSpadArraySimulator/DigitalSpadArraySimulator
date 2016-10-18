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
 * File        : config_importer.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 17 12:39:20 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef CONFIG_IMPORTER_BASE_H
#define CONFIG_IMPORTER_BASE_H

#include "map.hh"
#include "vector.hh"

/**
 * @brief Base class to import configuration.
 */
class ConfigImporter{
private:
    ConfigImporter(const ConfigImporter&);
    ConfigImporter& operator=(const ConfigImporter&);
    
protected:
    /**
     * @brief Default Constructor.
     */
    ConfigImporter() {}
    
public:
    /**
     * @brief Destructor.
     */
    virtual ~ConfigImporter() {}
    
    /**
     * @brief Get the properties for silicon.
     * 
     * @return Map< std::string, std::string >&
     */
    virtual const Map<std::string, std::string>& getSiliconConfig() const = 0;
    
    /**
     * @brief Get the properties for quench.
     * 
     * @return Map< std::string, std::string >&
     */
    virtual const Map<std::string, std::string>& getQuenchConfig() const = 0;
    
    /**
     * @brief Get the properties for spad.
     * 
     * @return Map< std::string, std::string >&
     */
    virtual const Map<std::string, std::string>& getSensorConfig() const = 0;
    
    /**
     * @brief Get the properties for spad matrix.
     * 
     * @return Map< std::string, std::string >&
     */
    virtual const Map<std::string, std::string>& getMatrixConfig() const = 0;
    
    /**
     * @brief Get the silicon optical properties.
     * 
     * @warning This function only clear the output parameters.
     * 
     * @param[out] wavelengths The wavelengths.
     * @param[out] coefficients The coefficients base on the wavelengths.
     */
    virtual void getSiliconOpticalProperties(Vector<double>& wavelengths, Vector<double>& coefficients) const;
};

#endif