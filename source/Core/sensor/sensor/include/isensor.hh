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
 * File        : isensor.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef I_SENSOR_H
#define I_SENSOR_H

#include "state.hh"

class ISensorConfiguration;
class Polygon;
class Photon;

struct Position2D;

/**
 * @brief Abstract class representing a sensor to be used in a sensor matrix.
 */
class ISensor {
private:
    ISensor(const ISensor&);
    ISensor& operator=(const ISensor&);
    
protected:
    /**
     * @brief Constructor.
     */
    ISensor();
    
    /**
     * @brief Constructor with a specific configuration.
     * 
     * @param configuration The configuration.
     */
    ISensor(ISensorConfiguration* configuration);
    
    /**
     * @brief The configuration to be used by all the sensors in the same matrix.
     */
    ISensorConfiguration* configuration;
    
    /**
     * @brief The polygon representing this specific sensor in the matrix.
     */
    Polygon* polygon;
    
    /**
     * @brief A time reference.
     * 
     * @see ISensor::update, ISensor::trigger
     */
    double time;
    
    /**
     * @brief The current state of the sensor.
     * 
     * @see ISensor::update, ISensor::trigger
     */
    State::StateType state;
    
public:
    /**
     * @brief Destructor.
     * 
     * @warning Will not delete the configuration since it's shared by every sensors in the matrix.
     */
    virtual ~ISensor();
    
    /**
     * @brief Update the sensor states.
     * 
     * @param elapsed Time elapsed since last update.
     */
    virtual void update(const double& elapsed);
    
    /**
     * @brief Reset the state of the sensor to State::READY.
     */
    virtual void reset();
    
    /**
     * @brief Check if a photon is absorbed inside this Sensor.
     * 
     * @param photon The photon to check.
     * @return bool True if the photon was absorbed, false otherwise.
     */
    virtual bool isAbsorbed(const Photon& photon) const = 0;
    
    /**
     * @brief Try to make the particle walk randomly until it reaches the depletion zone.
     * 
     * @param particle The particle that must try to reach the depletion zone.
     * @param meanLifetime The mean life time of a particle before it stops moving.
     * @param fromTop Indicate whether the particle is from the Top or the Bottom.
     * @param tau The exponential scale for the exponential distribution for the time between collisions. (\f$\text{scale}=\frac{1}{\lambda}\f$)
     * @param scalingFactor The scaling factor used to affect the random instantaneous velocity of the particle.
     * @return bool True if the particle has reached the depletion zone, false otherwise.
     */
    virtual bool randomWalk(Particle& particle, const double& meanLifetime, const bool& fromTop, const double& tau, const double& scalingFactor) const = 0;
    
    /**
     * @brief Try triggering the Sensor by hitting it with a particle.
     * 
     * @param particle The particle that hits the Sensor.
     * @return Avalanche* The pointer will be set to 0 if no avalanche was created.
     */
    virtual Avalanche* trigger(Particle* particle) = 0;
    
    /**
     * @brief Get the sensor configuration.
     * 
     * @return const ISensorConfiguration& The sensor configuration.
     */
    inline const ISensorConfiguration& getConfiguration() const {return *configuration;}
    
    /**
     * @brief Get the position representing the center of this sensor.
     * 
     * @return const Position2D& The center of this sensor.
     */
    const Position2D& getCenter() const;
};

#endif //I_SENSOR_H