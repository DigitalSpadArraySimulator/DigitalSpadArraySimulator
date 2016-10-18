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
 * File        : polygon.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Feb 26 09:44:39 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef POLYGON_ALGORITHMS_H
#define POLYGON_ALGORITHMS_H
#include "vector.hh"
#include "position.hh"

/**
 * @brief Class representing a geometrical regular polygon.
 */
class Polygon{
private:
    Polygon();
    Polygon(const Polygon&);
    Polygon& operator=(const Polygon&);

private:
    inline bool isBetweenLineY(const double& line1, const double& line2, const double& point) const;
    inline bool isLeftToLine(const Position2D& line1, const Position2D& line2, const Position2D& point) const;
    
    Vector<Position2D> vertices;
    double radius;
    double angle;
    Position2D center;

public:
    /**
     * @brief Create a regular polygon with specified parameters.
     * 
     * @param nbVertices The number of vertices.
     * @param radius The radius between the center and the vertices.
     * @param angle The angle offset of the first vertex.
     * @param center The polygon center.
     */
    Polygon(const unsigned int& nbVertices, const double& radius, const double& angle, const Position2D& center);
    
    /**
     * @brief Duplicate a polygon to another position.
     * 
     * @param polygon The polygon to duplicate.
     * @param center The center of this polygon.
     */
    Polygon(const Polygon& polygon, const Position2D& center);
    
    /**
     * @brief Destructor.
     */
    ~Polygon();
    
    /**
     * @brief Find out if a point is inside the polygon.
     * 
     * @param point The point.
     * @return bool true if inside, false if outside.
     * @see http://stackoverflow.com/q/11716268
     */
    bool contains(const Position2D& point) const;
    
    /**
     * @brief Get the center position of the polygon.
     * 
     * @return const Position2D& The center of the polygon.
     */
    inline const Position2D& getCenter() const {return center;}
};

#endif //POLYGON_ALGORITHMS_H