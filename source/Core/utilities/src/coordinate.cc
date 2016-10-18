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
 * File        : coordinate.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Feb 25 11:38:37 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "coordinate.hh"

Coordinate2D::Coordinate2D() 
: Coordinate2D(0, 0)
{}

Coordinate2D::~Coordinate2D()
{}

Coordinate2D::Coordinate2D(const int& x, const int& y)
: x(x)
, y(y)
{}

Coordinate2D::Coordinate2D(const Coordinate2D& other)
: Coordinate2D(other.x, other.y)
{}

Coordinate2D& Coordinate2D::operator=(const Coordinate2D& other)
{
    x = other.x;
    y = other.y;
    
    return *this;
}

bool Coordinate2D::operator==(const Coordinate2D& other)
{
    return x == other.x && y == other.y;
}


