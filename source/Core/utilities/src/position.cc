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
 * File        : position.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Feb 25 11:38:37 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "position.hh"
#include <math.h>

Position2D::Position2D()
: Position2D(0.0, 0.0)
{}


Position2D::Position2D(const Position2D& other)
: Position2D(other.x, other.y)
{}


Position2D::Position2D(const double& x, const double& y)
: x(x)
, y(y)
{}

Position2D& Position2D::operator=(const Position2D& other)
{
    this->x = other.x;
    this->y = other.y;
    return *this;
}

Position2D Position2D::operator+(const Position2D& other) const
{
    Position2D result = *this;
    return result += other;
}

Position2D& Position2D::operator+=(const Position2D& other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Position2D Position2D::operator-(const Position2D& other) const
{
    Position2D result = *this;
    return result -= other;
}

Position2D& Position2D::operator-=(const Position2D& other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

Position2D Position2D::operator*(const double& scalar) const
{
    Position2D result = *this;
    return result *= scalar;
}

Position2D Position2D::operator*=(const double& scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

double Position2D::calculateDistance(const Position2D& other) const
{
    double deltaX = this->x - other.x;
    double deltaY = this->y - other.y;
    return sqrt(deltaX*deltaX + deltaY*deltaY);
}

Position3D::Position3D()
: Position3D(0.0, 0.0, 0.0)
{}

Position3D::Position3D(const Position3D& other)
: Position3D(other.x, other.y, other.z)
{}

Position3D::Position3D(const double& x, const double& y, const double& z)
: Position2D(x, y)
, z(z)
{}

Position3D::Position3D(const Position2D& xy, const double& z)
: Position2D(xy)
, z(z)
{}

Position3D& Position3D::operator=(const Position3D& other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}

Position3D Position3D::operator+(const Position3D& other) const
{
    Position3D result = *this;
    return result += other;
}

Position3D& Position3D::operator+=(const Position3D& other)
{
    Position2D::operator+=(other);
    this->z += other.z;
    return *this;
}

Position3D Position3D::operator-(const Position3D& other) const
{
    Position3D result = *this;
    return result -= other;
}

Position3D& Position3D::operator-=(const Position3D& other)
{
    Position2D::operator-=(other);
    this->z -= other.z;
    return *this;
}

Position3D Position3D::operator*(const double& scalar) const
{
    Position3D result = *this;
    return result *= scalar;
}

Position3D Position3D::operator*=(const double& scalar)
{
    Position2D::operator*=(scalar);
    this->z *= scalar;
    return *this;
}
