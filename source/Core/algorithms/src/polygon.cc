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
 * File        : polygon.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Feb 26 09:44:39 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include <stdexcept>
#include <math.h>
#include "polygon.hh"


Polygon::Polygon(const unsigned int& nbVertices, const double& radius, const double& angle, const Position2D& center)
: radius(radius)
, angle(angle)
, center(center)
, vertices(Vector<Position2D>(nbVertices))
{
    if (nbVertices < 3) {
        throw std::invalid_argument("A polygon must have at least 3 vertices");
    }
    
    for (unsigned int i = 0; i < nbVertices; ++i) {
        double vertex_angle = 2 * M_PI * double(i)/double(nbVertices) + angle;
        double x = radius * cos(vertex_angle) + center.x;
        double y = radius * sin(vertex_angle) + center.y;
        vertices[i] = Position2D(x, y);
    }
}

Polygon::Polygon(const Polygon& polygon, const Position2D& center)
: radius(polygon.radius)
, angle(polygon.angle)
, center(center)
, vertices(Vector<Position2D>(polygon.vertices.size()))
{
    Position2D offset = this->center - polygon.center;
    for (unsigned int i = 0; i < polygon.vertices.size(); ++i) {
        this->vertices[i] = polygon.vertices[i] + offset;
    }
}

Polygon::~Polygon()
{
    vertices.clear();
}

bool Polygon::contains(const Position2D& point) const 
{
    int i, j;
    bool contains = false;
    
    if (this->center.calculateDistance(point) < this->radius) {
        // The algorithm was taken from here 
        // http://stackoverflow.com/questions/11716268/point-in-polygon-algorithm
        for (i = 0, j = vertices.size()-1; i < vertices.size(); j = i++) {
            if (isBetweenLineY(vertices[i].y, vertices[j].y, point.y) &&
                isLeftToLine(vertices[i], vertices[j], point)) {
                contains = !contains;
            }
        }
    }
    return contains;
}

bool Polygon::isBetweenLineY(const double& line1, const double& line2, const double& point) const
{
    return (line1 > point) != (line2 > point);
}

bool Polygon::isLeftToLine(const Position2D& line1, const Position2D& line2, const Position2D& point) const
{
    return point.x < (line2.x - line1.x) * (point.y - line1.y) / (line2.y - line1.y) + line1.x;
}
