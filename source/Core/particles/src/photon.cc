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
 * File        : photon.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Feb 26 11:15:54 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "photon.hh"
#include <stdexcept>

Photon::Photon(const double& globalTime, 
               const Position2D& penetrationPoint, 
               const Position3D& postMomentum)
: Photon(globalTime, penetrationPoint, postMomentum, 0.0)
{}

Photon::Photon(const double& globalTime, 
               const Position2D& penetrationPoint, 
               const Position3D& postMomentum, 
               const double& waveLength)
: Photon(globalTime, penetrationPoint, postMomentum, PHOTON, waveLength)
{}

Photon::Photon(const double& globalTime, 
               const Position2D& penetrationPoint, 
               const Position3D& postMomentum, 
               const Particle::ParticleType& type, 
               const double& waveLength)
: Particle(globalTime, type, Coordinate2D(-1, -1), Position3D(0.0, 0.0, 0.0))
, penetrationPoint(penetrationPoint)
, postMomentum(postMomentum)
, waveLength(waveLength)
{
    if (type != PHOTON
        && type != CERENKOV_PHOTON
        && type != PROMPT_PHOTON) {
        throw std::invalid_argument("Given type is not a photon");
    }
}

Photon::~Photon()
{}

void Photon::calculateAbsorptionPoint(const double& maxDepth)
{
    position.x = penetrationPoint.x +  postMomentum.x * maxDepth;
    position.y = penetrationPoint.y +  postMomentum.y * maxDepth;
    position.z = -postMomentum.z * maxDepth;
}
