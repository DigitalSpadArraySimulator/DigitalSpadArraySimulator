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
 * File        : isensor_factory.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef I_SENSOR_FACTORY_H
#define I_SENSOR_FACTORY_H

class ISensor;
class ISensorConfiguration;

struct Position2D;

/**
 * @brief Abstract class used to create ISensor.
 */
class ISensorFactory {
private:
    ISensorFactory(const ISensorFactory&);
    ISensorFactory& operator=(const ISensorFactory&);
    
protected:
    /**
     * @brief The configuration that will be shared by all sensor created by this factory.
     */
    ISensorConfiguration* sensorConfiguration;
    
    /**
     * @brief Constructor.
     */
    ISensorFactory();
    
    /**
     * @brief Will calculate the radius to the vertices from the radius to the side of the polygon.
     * 
     * @warning The configuration must be set before calling this function.
     */
    virtual void calculateCorrectedRadius();
    
public:
    /**
     * @brief Destructor.
     * 
     * @warning Will not delete the sensors configuration.
     */
    virtual ~ISensorFactory();
    
    /**
     * @brief Create a sensor.
     * 
     * @param sensorCenter The sensor's polygon center.
     * @return ISensor*
     */
    virtual ISensor* build(const Position2D& sensorCenter) = 0;
    
    /**
     * @brief Set the configuration that will be shared by all sensor created by this factory.
     * 
     * @param sensorConfiguration The configuration.
     */
    virtual void setSensorConfiguration(ISensorConfiguration* sensorConfiguration);
};

#endif //I_SENSOR_FACTORY_H