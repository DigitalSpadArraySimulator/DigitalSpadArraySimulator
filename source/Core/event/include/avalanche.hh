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
 * File        : avalanche.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 9 09:29:49 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef AVALANCHE_EVENT_H
#define AVALANCHE_EVENT_H

#include "coordinate.hh"
#include "particle.hh"

/**
 * @brief Class containing information about an avalanche
 */
class Avalanche {
private:
    Avalanche();
    Avalanche(const Avalanche&);
    Avalanche& operator=(const Avalanche&);
    
    Coordinate2D spadCoord;
    Particle* particle;
    double jitter;
    bool masked;
    
public:
    /**
     * @brief Create an avalanche from a particle and a jitter time.
     * 
     * The created avalanche masked value will be false by default.
     * 
     * @param particle The particle that causes the avalanche.
     * @param jitter The jitter time of the avalanche.
     */
    Avalanche(Particle* particle, const double& jitter);
    
    /**
     * @brief Create an avalanche from a particle, a jitter time and a specified masked value
     * 
     * @param particle The particle that causes the avalanche.
     * @param jitter The jitter time of the avalanche.
     * @param masked If true, the avalanche was never triggered because of the Spad state.
     */
    Avalanche(Particle* particle, const double& jitter, const bool& masked);
    
    /**
     * @brief Destructor
     * 
     * @warning Will delete the particle.
     */
    ~Avalanche();
    
    /**
     * @brief Get what type of particle triggered this avalanche.
     * 
     * @return Particle::ParticleType
     */
    Particle::ParticleType getTriggerType() const;
    
    /**
     * @brief Get the time when the avalanche occured
     * 
     * @return double The particle global time +  the avalanche jitter time
     */
    double getGlobalTime() const;
    
    /**
     * @brief Get if the avalanch is masked or not
     * 
     * @return bool
     */
    inline bool isMasked() const {return masked;}
    
    /**
     * @brief Get the coordinate of the spad where the avalanche occured
     * 
     * @return const Coordinate2D&
     */
    inline const Coordinate2D& getSpadCoordinate() {return spadCoord;}
};

#endif //AVALANCHE_EVENT_Hs