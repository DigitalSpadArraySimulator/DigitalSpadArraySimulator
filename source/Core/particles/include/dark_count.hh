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
 * File        : dark_count.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 9 15:09:28 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef DARK_COUNT_PARTICLE_H
#define DARK_COUNT_PARTICLE_H

#include "particle.hh"

/**
 * @brief A particle that originates from thermal noises and tries to start an avalanch.
 */
class DarkCount : public Particle {
private:
    DarkCount();
    DarkCount(const DarkCount&);
    DarkCount& operator=(const DarkCount&);

public:
    /**
     * @brief Constructor.
     * 
     * @param globalTime The time when to hit the sensor.
     * @param spadCoord The coordinate of the sensor to hit.
     * @param position The position where to hit the sensor.
     */
    DarkCount(const double& globalTime, const Coordinate2D& spadCoord, const Position3D& position);
    
    /**
     * @brief Destructor.
     */
    virtual ~DarkCount() {}
};

#endif //DARK_COUNT_PARTICLE_H
