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
 * File        : photon.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Feb 26 11:15:54 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef PHOTON_PARTICLES_H
#define PHOTON_PARTICLES_H

#include "particle.hh"

/**
 * @brief Derived Particle representing a photon.
 */
class Photon : public Particle{
private:
    Position2D penetrationPoint;
    Position3D postMomentum;
    double waveLength;
    
public:
    /**
     * @brief Constructor.
     * @warning The type will be Particle::PHOTON and the wavelength will be 0nm.
     * @param globalTime The time when the photon hits the sensor.
     * @param penetrationPoint The 2D position where the photon hits the sensor surface.
     * @param postMomentum The momentum of the photon after it hits the surface.
     */
    Photon(const double& globalTime, 
           const Position2D& penetrationPoint, 
           const Position3D& postMomentum);
    
    /**
     * @brief Constructor.
     * @warning The type will be Particle::PHOTON.
     * @param globalTime The time when the photon hits the sensor.
     * @param penetrationPoint The 2D position where the photon hits the sensor surface.
     * @param postMomentum The momentum of the photon after it hits the surface.
     * @param waveLength The wavelength of the photon.
     */
    Photon(const double& globalTime, 
           const Position2D& penetrationPoint, 
           const Position3D& postMomentum, 
           const double& waveLength);
    
    /**
     * @brief Constructor.
     * @warning The given type should be Particle::PHOTON, Particle::CERENKOV_PHOTON or Particle::PROMPT_PHOTON.
     * @param globalTime The time when the photon hits the sensor.
     * @param penetrationPoint The 2D position where the photon hits the sensor surface.
     * @param postMomentum The momentum of the photon after it hits the surface.
     * @param type The type of the photon.
     * @param waveLength The wavelength of the photon.
     */
    Photon(const double& globalTime, 
           const Position2D& penetrationPoint, 
           const Position3D& postMomentum, 
           const ParticleType& type, 
           const double& waveLength);
    
    /**
     * @brief Destructor.
     */
    virtual ~Photon();
    
    /**
     * @brief Set the coordinate of the sensor hit by the photon.
     * @param coord The coordinate corresponding to the sensor position in the matrix.
     */
    inline void setSensorCoordinate(const Coordinate2D& coord) { this->sensorCoordinate = coord; }
    
    /**
     * @brief Return the position where the photon was absorbed inside the sensor.
     * @return const Position3D&
     */
    inline const Position3D& getAbsortptionPoint() const { return this->position; }
    
    /**
     * @brief Return the position where the photon hits the sensor on its surface.
     * @return const Position2D&
     */
    inline const Position2D& getPenetrationPoint() const { return this->penetrationPoint; }
    
    /**
     * @brief Get the photon's wavelength.
     * @return const double& The wavelength in nm.
     */
    inline const double& getWavelength() const { return this->waveLength; }
    
    /**
     * @brief Calculate the photon absorption point inside the sensor based on the maximum depth and the post momentum.
     * @param maxDepth The maximum depth that this photon could reach with a post momentum of (1, 1, 1).
     */
    void calculateAbsorptionPoint(const double& maxDepth);
};

#endif //PHOTON_PARTICLES_H