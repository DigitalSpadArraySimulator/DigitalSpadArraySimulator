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
 * File        : sipm_factory.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Apr 13 11:30:25 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef SIPM_FACTORY_SENSOR_H
#define SIPM_FACTORY_SENSOR_H

#include "spad_factory.hh"

#include "vector.hh"

class PDEBehavior;
struct Position2D;

/**
 * @brief Derived ISensorFactory that creates Sipm.
 */
class SipmFactory : public SpadFactory {
private:
    SipmFactory(const SipmFactory&);
    SipmFactory& operator=(const SipmFactory&);
    
public:
    /**
     * @brief Constructor.
     * 
     * The PDEBehavior will be detected from the ISensorConfiguration.
     */
    SipmFactory();
    
    /**
     * @brief Constructor with a specific PDEBehavior.
     * 
     * @param pde The PDEBehavior used by every sensor.
     */
    SipmFactory(PDEBehavior* pde);
    
    /**
     * @brief Destructor.
     */
    virtual ~SipmFactory();
    
    /**
     * @brief Build a sensor based on it's center.
     * 
     * @param sensorCenter The center of the sensor.
     * @return ISensor*
     */
    virtual ISensor* build(const Position2D& sensorCenter) override;
};

#endif //SIPM_FACTORY_SENSOR_H