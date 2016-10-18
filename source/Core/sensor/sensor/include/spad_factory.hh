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
 * File        : spad_factory.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef SPAD_FACTORY_SENSOR_H
#define SPAD_FACTORY_SENSOR_H

#include "isensor_factory.hh"
#include "vector.hh"

class Polygon;
class PDEBehavior;
struct Position2D;

/**
 * @brief Derived ISensorFactory that creates Spad.
 */
class SpadFactory : public ISensorFactory {
private:
    SpadFactory(const SpadFactory&);
    SpadFactory& operator=(const SpadFactory&);

protected:
    /**
     * @brief The polygon model of every sensor to be created.
     */
    Polygon* model;
    
    /**
     * @brief Create the polygon model from the ISensorConfiguration.
     * 
     * @warning The ISensorFactory::sensorConfiguration must be set before this call.
     */
    virtual void createModel();
    
    /**
     * @brief Calculate the depletion zone of the SPADs based on the ISensorConfiguration.
     * 
     * @warning The ISensorFactory::sensorConfiguration must be set before this call.
     */
    virtual void calculateDepletionZone();
    
public:
    /**
     * @brief Constructor.
     * 
     * The PDEBehavior will be detected from the ISensorConfiguration.
     */
    SpadFactory();
    
    /**
     * @brief Constructor with a specific PDEBehavior.
     * 
     * @param pde The PDEBehavior used by every sensor.
     */
    SpadFactory(PDEBehavior* pde);
    
    /**
     * @brief Destructor.
     * 
     * @warning Will delete the polygon model.
     * 
     * @see ISensorFactory::~ISensorFactory.
     */
    virtual ~SpadFactory();
    
    /**
     * @brief Set the configuration that will be given to all sensor.
     * 
     * Also generate the polygon model and calculate the depletion zone based on the configuration.
     * 
     * @param sensorConfiguration The configuration.
     */
    virtual void setSensorConfiguration(ISensorConfiguration* sensorConfiguration) override;
    
    /**
     * @brief Build a sensor based on it's center.
     * 
     * @param sensorCenter The center of the sensor.
     * @return ISensor*
     */
    virtual ISensor* build(const Position2D& sensorCenter) override;
};

#endif //SPAD_FACTORY_SENSOR_H