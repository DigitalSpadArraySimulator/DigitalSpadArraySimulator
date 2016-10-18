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
 * File        : array_algorithm.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 07:56:44 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef ARRAY_ALGORITHMS_H
#define ARRAY_ALGORITHMS_H

#include "vector.hh"
#include "ptr_ref.hh"
/**
 * @brief Static class that wraps a heap sort algorithm.
 */
class HeapSort{
private:
    HeapSort();
    ~HeapSort();
    HeapSort(const HeapSort&);
    HeapSort& operator=(const HeapSort&);
    
    inline static int parent(const int& i){
        return (i - 1) / 2;
    }
    
    inline static int leftChild(const int& i){
        return 2 * i + 1;
    }
    
    inline static int rightChild(const int& i){
        return 2 * i + 2;
    }
    
    template<typename T>
    static void swap(Vector<T>& vector, const int& a, const int& b);
    
    template<typename T>
    static void siftDown(Vector<T>& vector, const int& start, const int& end);
    
    template<typename T>
    static void heapify(Vector<T>& vector);
    
public:
    /**
     * @brief Sort the given vector.
     * 
     * If T is a pointer, the sort is done using the pointed object.
     * 
     * @warning T must implement the operators < and =.
     * 
     * @param[in,out] vector The vector to sort.
     */
    template<typename T>
    static void heapSort(Vector<T>& vector);
};

/**
 * @brief Static class that wraps a dichotomic search algorithm.
 */
class Dichotomic{
private:
    Dichotomic();
    ~Dichotomic();
    Dichotomic(const Dichotomic&);
    Dichotomic& operator=(const Dichotomic&);
    
    template<typename T>
    static void isolateIndex(const Vector<T>& vector, const T& element, int& start, int& end);

public:
    /**
     * @brief Find the index where to insert a data to keep the vector sorted.
     * 
     * If T is a pointer, the algorithm uses the pointed object.
     * 
     * @warning The vector must be sorted before this call.
     * 
     * @warning T must implement the operators >, < and ==.
     * 
     * @param vector A sorted vector.
     * @param element The element.
     * @return int The position where to insert the element to keep the vector sorted.
     */
    template<typename T>
    static int findInsertIndex(const Vector<T>& vector, const T& element);
    
    /**
     * @brief Find the index of the smallest closest item.
     * 
     * Ex. 1 : vector = [2, 3, 5], element = 4. Return 1 (for 3).
     * Ex. 2 : vector = [3, 4, 5], element = 4. Return 1 (for 4).
     * 
     * If T is a pointer, the algorithm uses the pointed object.
     * 
     * @warning The vector must be sorted before this call.
     * 
     * @warning T must implement the operators >, <, == and <=.
     * 
     * @param vector A sorted vector.
     * @param element The element.
     * @return int The position of the smallest closest element.
     */
    template<typename T>
    static int findSmallerClosestIndex(const Vector<T>& vector, const T& element);
    
    /**
     * @brief Insert the element in the vector in a way to keep the vector sorted.
     * 
     * If T is a pointer, the algorithm uses the pointed object.
     * 
     * @warning The vector must be sorted before this call.
     * 
     * @warning T must implement the operators >, < and ==.
     * 
     * @param vector A sorted vector.
     * @param element The element to insert.
     */
    template<typename T>
    static void insert(Vector<T>& vector, const T& element);
};

#include "array_algorithm.hpp"

#endif // ARRAY_ALGORITHMS_H