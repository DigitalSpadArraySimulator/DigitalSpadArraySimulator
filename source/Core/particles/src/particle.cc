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
 * File        : particle.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Feb 25 11:38:37 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "particle.hh"

#include <math.h>

#include "random.hh"

Particle::Particle(const double& globalTime, const Particle::ParticleType& type, const Coordinate2D& spadCoordinate, const Position3D& position)
: globalTime(globalTime)
, type(type)
, sensorCoordinate(spadCoordinate)
, position(position)
, children(Children())
{}

Particle::Particle(const Particle& other)
: globalTime(other.globalTime)
, type(other.type)
, sensorCoordinate(other.sensorCoordinate)
, position(other.position)
, children(Children())
{}

Particle::Particle(Particle* parent, const double& globalTime, const Particle::ParticleType& type, const Coordinate2D& spadCoordinate, const Position3D& position) 
: Particle(globalTime, type, spadCoordinate, position)
{
    parent->children.push_back(this);
}

Particle::~Particle()
{
    children.clear();
}

bool Particle::operator<(const Particle& other) const 
{
    return this->globalTime < other.globalTime;
}

bool Particle::operator>(const Particle& other) const 
{
    return this->globalTime > other.globalTime;
}

bool Particle::operator<=(const Particle& other) const 
{
    return !((*this)>other);
}

bool Particle::operator>=(const Particle& other) const 
{
    return !((*this)<other);
}

bool Particle::operator==(const Particle& other) const 
{
    return this->globalTime == other.globalTime;
}

bool Particle::operator!=(const Particle& other) const 
{
    return !((*this) == other);
}

double Particle::MoveRandomly(const double& tau, const double& scalingFactor)
{
    double dt = RandomGenerator::exponential(1/tau);
    double vinst = scalingFactor * RandomGenerator::chiSquared(3.0);
    double dL = dt * vinst;
    double phi = M_PI * RandomGenerator::rand();
    double theta = 2 * M_PI * RandomGenerator::rand();
    double lateral = dL * sin(phi);
    Position3D offset = Position3D(lateral * cos(theta),
                                   lateral * sin(theta),
                                   dL * cos(phi));
    this->position += offset;
    this->globalTime += dt * 1.0e9;
    return dt;
}
