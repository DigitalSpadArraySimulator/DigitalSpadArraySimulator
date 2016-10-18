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
 * File        : particle.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Feb 25 11:38:37 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef PARTICLE_PARTICLES_H
#define PARTICLE_PARTICLES_H

#include "coordinate.hh"
#include "position.hh"
#include "vector.hh"

/**
 * @brief Abstract class for every particles.
 */
class Particle{
public:
    /**
     * @enum ParticleType
     * @brief type given by subclasses.
     */
    enum ParticleType {
        PHOTON = 1, ///<Photon
        THERMAL_NOISE = 2, ///<DarkCount
        AFTERPULSING = 3, ///<Afterpulse
        OPTICAL_CROSSTALK = 4, ///<Crosstalk
        CERENKOV_PHOTON = 11, ///<Cerenkov Photon
        PROMPT_PHOTON = 21 ///<Prompt Photon
    };

private:
    Particle();
    typedef Vector<Particle*> Children;
    
protected:
    /**
     * @brief Constructor.
     * 
     * @param globalTime The time when to hit the sensor.
     * @param type The type of particle.
     * @param sensorCoordinate The Coordinate of the sensor to hit.
     * @param position The position where to hit the sensor.
     */
    Particle(const double& globalTime, 
             const ParticleType& type, 
             const Coordinate2D& sensorCoordinate, 
             const Position3D& position);
    
    /**
     * @brief Constructor.
     * 
     * @param parent The parent Particle.
     * @param globalTime The time when to hit the sensor.
     * @param type The type of particle.
     * @param sensorCoordinate The Coordinate of the sensor to hit.
     * @param position The position where to hit the sensor.
     */
    Particle(Particle* parent, 
             const double& globalTime, 
             const ParticleType& type, 
             const Coordinate2D& sensorCoordinate, 
             const Position3D& position);
    
    double globalTime; //!< The time when the particle hit the sensor.
    ParticleType type; //!< The type of the particle.
    Coordinate2D sensorCoordinate; //!< The Coordinate of the sensor hit by the particle.
    Position3D position; //!< The position of the particle.
    Children children; //!< A vector of children particle.
    
public:
    /**
     * @brief Destructor.
     * @warning Will not delete the children.
     */
    virtual ~Particle();
    
    /**
     * @brief Copy constructor will copy every thing except children.
     * @param other The one to copy.
     */
    Particle(const Particle& other);
    
    /**
     * @brief Use the globalTime to determine if it's smaller then the other.
     * @param other The others Particle used for comparing.
     * @return bool
     */
    bool operator<(const Particle& other) const;
    
    /**
     * @brief Use the globalTime to determine if it's bigger then the other.
     * @param other The others Particle used for comparing.
     * @return bool
     */
    bool operator>(const Particle& other) const;
    
    /**
     * @brief Use the globalTime to determine if it's smaller or equal then the other.
     * @param other The others Particle used for comparing.
     * @return bool
     */
    bool operator<=(const Particle& other) const;
    
    /**
     * @brief Use the globalTime to determine if it's bigger or equal then the other.
     * @param other The others Particle used for comparing.
     * @return bool
     */
    bool operator>=(const Particle& other) const;
    
    /**
     * @brief Use the globalTime to determine if it's equal to the other.
     * @param other The others Particle used for comparing.
     * @return bool
     */
    bool operator==(const Particle& other) const;
    
    /**
     * @brief Use the globalTime to determine if it's not equal to the other.
     * @param other The others Particle used for comparing.
     * @return bool
     */
    bool operator!=(const Particle& other) const;
    
    /**
     * @brief Return the globalTime of the Particle.
     * @return const double&
     */
    inline const double& getGlobalTime() const {return globalTime;}
    
    /**
     * @brief Return the 3D Position of the particle.
     * @return const Position3D&
     */
    inline const Position3D& getPosition() const {return position;}
    
    /**
     * @brief Set the Position of the Z axis of the particle. Keep X and Y unchanged.
     * @return void
     */
    inline void setDepth(const double& z) {position.z = z;}
    
    /**
     * @brief Get the coordinate in the matrix of the sensor where the particle is.
     * @return const Coordinate2D&
     */
    inline const Coordinate2D& getSensorCoordinate() const {return sensorCoordinate;}
    
    /**
     * @brief Get the particle's type.
     * @return Particle::ParticleType&
     */
    inline const ParticleType& getParticleType() const {return type;}
    
    /**
     * @brief Make a move in a random direction according to an exponential scale and a scaling factor.
     * @param tau The exponential scale for the exponential distribution for the time between collisions. (\f$\text{scale}=\frac{1}{\lambda}\f$)
     * @param scalingFactor The scaling factor used to affect the random instantaneous velocity.
     * @return double The movement duration.
     */
    double MoveRandomly(const double& tau, const double& scalingFactor);
    
    /**
     * @brief Add time to the globalTime.
     */
    inline void addTime(const double& time) {globalTime += time;}
};


#endif // PARTICLE_PARTICLES_H