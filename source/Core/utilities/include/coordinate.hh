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
 * File        : coordinate.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Feb 25 11:38:37 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef COORDINATE_UTILITIES_H
#define COORDINATE_UTILITIES_H

/**
 * @brief 2 dimensions coordinate containing int (x, y)
 */
struct Coordinate2D {
public:
    /**
     * @brief Default constructor (0, 0).
     */
    Coordinate2D();
    
    /**
     * @brief Destructor.
     */
    ~Coordinate2D();
    
    /**
     * @brief Constructor with sepcified (x, y).
     * @param x 
     * @param y
     */
    Coordinate2D(const int& x, const int& y);
    
    /**
     * @brief Copy constructor.
     * @param other The one to copy.
     */
    Coordinate2D(const Coordinate2D& other);
    
    /**
     * @brief Asignation operator.
     * @param other The one to copy.
     * @return Coordinate2D&
     */
    Coordinate2D& operator=(const Coordinate2D& other);
    
    /**
     * @brief Return true if both x and y are the same.
     * @param other The one to compare with.
     * @return bool
     */    
    bool operator==(const Coordinate2D& other);
    
    /**
     * @brief The x coordinate.
     */
    int x;
    
    /**
     * @brief The y coordinate.
     */
    int y;
};

#endif //COORDINATE_UTILITIES_H