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
 * File        : position.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Feb 25 11:38:37 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef POSITION_UTILITIES_H
#define POSITION_UTILITIES_H

/**
 * @brief 2D position (x, y).
 */
struct Position2D{
public:
    /**
     * @brief Constructor (0.0, 0.0).
     */
    Position2D();
    
    /**
     * @brief Constructor (x, y).
     * @param x x.
     * @param y y.
     */
    Position2D(const double& x, const double& y);
    
    /**
     * @brief Copy constructor.
     * @param other The one to copy (x, y).
     */
    Position2D(const Position2D& other);
    
    /**
     * @brief Asignation operator.
     * 
     * @param other The one to copy (x, y).
     * @return Position2D& A reference to this position with new value.
     */
    Position2D& operator=(const Position2D& other);
    
    /**
     * @brief Create a new position to the sum of the two \f$(x_1+x_2, y_1+y_2)\f$.
     * @param other \f$(x_2, y_2)\f$.
     * @return Position2D The created position.
     */
    Position2D operator+(const Position2D& other) const;
    
    /**
     * @brief Move position to the sum of the two  \f$(x_1+x_2, y_1+y_2)\f$.
     * @param other \f$(x_2, y_2)\f$.
     * @return Position2D A reference to this position with new value.
     */
    Position2D& operator+=(const Position2D& other);
    
    /**
     * @brief Create a new position to the difference of the two \f$(x_1-x_2, y_1-y_2)\f$.
     * @param other \f$(x_2, y_2)\f$.
     * @return Position2D The created position.
     */
    Position2D operator-(const Position2D& other) const;
    
    /**
     * @brief Move position to the difference of the two \f$(x_1-x_2, y_1-y_2)\f$.
     * @param other \f$(x_2, y_2)\f$.
     * @return Position2D A reference to this position with new value.
     */
    Position2D& operator-=(const Position2D& other);
    
    /**
     * @brief Create a new position to the scalar product to position \f$(x*s, y*s)\f$.
     * @param scalar \f$s\f$.
     * @return Position2D The created position.
     */
    Position2D operator*(const double& scalar) const;
    
    /**
     * @brief Move position to the scalar product to position \f$(x*s, y*s)\f$.
     * @param scalar \f$s\f$.
     * @return Position2D A reference to this position with new value.
     */
    Position2D operator*=(const double& scalar);
    
    /**
     * @brief Calculate the distance between this position and the other.
     * 
     * \f[\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}\f].
     * 
     * @param other \f$(x_2, y_2)\f$.
     * @return double The distance.
     * @see https://en.wikipedia.org/wiki/Pythagorean_theorem
     */
    double calculateDistance(const Position2D& other) const;
    
    /**
     * @brief The x position.
     */
    double x;
    
    /**
     * @brief The y position.
     */
    double y;
};

/**
 * @brief 3D position (x, y, z)
 */
struct Position3D : public Position2D {
public:
    /**
     * @brief Constructor (0.0, 0.0, 0.0).
     */
    Position3D();
    
    /**
     * @brief Constructor (x, y, z).
     * @param x x.
     * @param y y.
     * @param z z.
     */
    Position3D(const double& x, const double& y, const double& z);
    
    /**
     * @brief Constructor (x, y, z).
     * @param xy (x, y).
     * @param z z.
     */
    Position3D(const Position2D& xy, const double& z);
    
    /**
     * @brief Copy constructor.
     * @param other The one to copy (x, y, z).
     */
    Position3D(const Position3D& other);
    
    /**
     * @brief Asignation operator.
     * 
     * @param other The one to copy (x, y, z).
     * @return Position3D& A reference to this position with new value.
     */
    Position3D& operator=(const Position3D& other);
    
    /**
     * @brief Create a new position to the sum of the two \f$(x_1+x_2, y_1+y_2, z_1+z_2)\f$.
     * @param other \f$(x_2, y_2, z_2)\f$.
     * @return Position3D The created position.
     */
    Position3D operator+(const Position3D& other) const;
    /**
     * @brief Move position to the sum of the two \f$(x_1+x_2, y_1+y_2, z_1+z_2)\f$.
     * @param other \f$(x_2, y_2, z_2)\f$.
     * @return Position3D A reference to this position with new value.
     */
    Position3D& operator+=(const Position3D& other);
    /**
     * @brief Create a new position to the difference of the two \f$(x_1-x_2, y_1-y_2, z_1-z_2)\f$.
     * @param other \f$(x_2, y_2, z_2)\f$.
     * @return Position3D The created position.
     */
    Position3D operator-(const Position3D& other) const;
    /**
     * @brief Move position to the difference of the two \f$(x_1-x_2, y_1-y_2, z_1-z_2)\f$.
     * @param other \f$(x_2, y_2, z_2)\f$.
     * @return Position3D A reference to this position with new value.
     */
    Position3D& operator-=(const Position3D& other);
    
    /**
     * @brief Create a new position to the scalar product to position \f$(x*s, y*s, z*s)\f$.
     * @param scalar \f$s\f$.
     * @return Position3D The created position.
     */
    Position3D operator*(const double& scalar) const;
    /**
     * @brief Move position to the scalar product to position \f$(x*s, y*s, z*s)\f$.
     * @param scalar \f$s\f$.
     * @return Position3D A reference to this position with new value.
     */
    Position3D operator*=(const double& scalar);
    
    /**
     * @brief The z position.
     */
    double z;
};

#endif //POSITION_UTILITIES_H