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
 * File        : vector.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 2 15:19:04 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef VECTOR_UTILITIES_H
#define VECTOR_UTILITIES_H

#include <vector>

/**
 * @brief Specialized vector that can delete items if needed.
 */
template<typename T>
class Vector : public std::vector<T>{
public:
    /**
     * @brief Constructor.
     */
    Vector();
    
    /**
     * @brief Create the vector and create n default item.
     * @param count The number of item to create.
     * @warning T must have a default constructor T()
     */
    Vector(const int& count);
    
    /**
     * @brief Create the vector and create n default item.
     * @param count The number of item to create.
     * @param value The value to assign to every created item.
     * @warning T must have a copie constructor T()
     */
    Vector(const int& count, const T& value);
    
    /**
     * @brief Will clear the vector, it will not delete the items.
     */
    virtual ~Vector();
    
    /**
     * @brief Empty the vector and delete each item.
     */
    void clearAndDelete();
    
    /**
     * @brief Return an iterator pointing to wanted element.
     * 
     * Will do a linear search.
     * @param element The wanted element.
     * @return Vector< T >::iterator A value equal to Vector.end() is returned if not found.
     */
    typename Vector<T>::iterator find(const T& element);
    
    /**
     * @brief Return an const_iterator pointing to wanted element.
     * 
     * Will do a linear search.
     * @param element The wanted element.
     * @return Vector< T >::const_iterator A value equal to Vector.end() is returned if not found.
     */
    typename Vector<T>::const_iterator find(const T& element) const;
    
    /**
     * @brief Erase and delete the item pointed by the iterator.
     * @param it An iterator pointing to the element to remove.
     * @return Vector< T >::iterator Return a iterator pointing to the item replacing the one erased.
     * @see http://www.cplusplus.com/reference/vector/vector/erase/
     */
    typename Vector<T>::iterator eraseAndDelete(const typename Vector<T>::iterator& it);
    
    /**
     * @brief Will apply the += operator for every item.
     * 
     * \f[(v_1[0]=v_1[0]+v_2[0], v_1[1]=v_1[1]+v_2[1], ..., v_1[n]=v_1[n]+v_2[n])\f]
     * Where \f$n\f$ is the smallest size of the two Vector.
     * 
     * If T is a pointer, a reference to the pointed object will be used instead of the pointer.
     * 
     * @warning T must implement the operator +=.
     * 
     * @param other \f$v_2\f$.
     */
    void operator+=(const Vector<T>& other);
    
    /**
     * @brief Return the smallest item inside the Vector.
     * 
     * Will loop over every item.
     * 
     * If T is a pointer, a reference to the pointed object will be used instead of the pointer.
     * 
     * @warning T must implement the operator <.
     * 
     * @return T
     */
    T min() const;
    
    /**
     * @brief Return the biggest item inside the Vector.
     * 
     * Will loop over every item.
     * 
     * If T is a pointer, a reference to the pointed object will be used instead of the pointer.
     * 
     * @warning T must implement the operator >.
     * 
     * @return T
     */
    T max() const;
};

#include "vector.hpp"

#endif //VECTOR_UTILITIES_H