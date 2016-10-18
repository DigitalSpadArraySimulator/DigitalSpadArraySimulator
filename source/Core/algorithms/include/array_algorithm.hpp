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
 * File        : array_algorithm.hpp
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 07:56:44 2016 -0500 by valentin
 * 
 * FILE_INFO_END */

#include "ptr_ref.hh"
#include "vector.hh"

template<typename T>
void HeapSort::swap(Vector<T>& vector, const int& a, const int& b)
{
    T temp = vector[a];
    vector[a] = vector[b];
    vector[b] = temp;
}

template<typename T>
void HeapSort::siftDown(Vector<T>& vector, const int& start, const int& end)
{
    int root = start;
    int lChild, rChild, swap;
    
    while (leftChild(root) <= end){
        lChild = leftChild(root);
        rChild = rightChild(root);
        swap = root;
        
        if (ref(vector[swap]) < ref(vector[lChild])) {
            swap = lChild;
        }
        if (rChild <= end && ref(vector[swap]) < ref(vector[rChild])){
            swap = rChild;
        }
        if (swap == root){
            return;
        } else {
            HeapSort::swap(vector, root, swap);
            root = swap;
        }
    }
}

template<typename T>
void HeapSort::heapify(Vector<T>& vector)
{
    int start = parent(vector.size());
    
    while (start >= 0){
        siftDown(vector, start, vector.size() - 1);
        --start;
    }
}

template<typename T>
void HeapSort::heapSort(Vector<T>& vector)
{
    heapify(vector);
    int end = vector.size() - 1;
    
    while (end > 0){
        swap(vector, end, 0);
        --end;
        siftDown(vector, 0, end);
    }
}

template<typename T>
void Dichotomic::isolateIndex(const Vector<T>& vector, const T& element, int& start, int& end)
{
    int middle;
    
    while (start + 1 < end){
        middle = (end - start) / 2 + start;
        if (ref(vector[middle]) > ref(element)){
            end = middle;
            continue;
        }
        if (ref(vector[middle]) < ref(element)){
            start = middle;
            continue;
        }
        if (ref(vector[middle]) == ref(element)){
            start = middle;
            end = middle + 1;
        }
    }
}

template<typename T>
int Dichotomic::findInsertIndex(const Vector<T>& vector, const T& element)
{
    int start = 0;
    int end = vector.size() - 1;
    int index;
    
    isolateIndex(vector, element, start, end);
    
    if (end != -1 && ref(element) < ref(vector[start])){
        index = start;
    } else if (end != -1 && ref(element) > ref(vector[end])) {
        index = end + 1;
    } else {
        index = end;
    }
    
    return index;
}

template<typename T>
int Dichotomic::findSmallerClosestIndex(const Vector<T>& vector, const T& element)
{
    int start = 0;
    int end = vector.size() - 1;
    int index;
    
    isolateIndex(vector, element, start, end);
    
    if (end == -1 || ref(vector[end]) <= ref(element)){
        index = end;
    } else {
        index = start;
    }
    
    return index;
}

template<typename T>
void Dichotomic::insert(Vector<T>& vector, const T& element)
{
    int index = findInsertIndex(vector, element);
    typename Vector<T>::iterator it = vector.begin();
    vector.insert(it + index, element);
}