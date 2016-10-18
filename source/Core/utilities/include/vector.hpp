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
 * File        : vector.hpp
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 2 15:19:04 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include <stdexcept>
#include "ptr_ref.hh"

template<typename T>
Vector<T>::Vector() : std::vector<T>()
{}

template<typename T>
Vector<T>::Vector(const int& count)
: std::vector<T>(count)
{}

template<typename T>
Vector<T>::Vector(const int& count, const T& value)
: std::vector<T>(count, value)
{}

template<typename T>
Vector<T>::~Vector()
{
    this->clear();
}

template<typename T>
void Vector<T>::clearAndDelete()
{
    for (typename Vector<T>::iterator it = this->begin(); it != this->end(); ) {
        delete *it;
        it = this->erase(it);
    }
}

template<typename T>
typename Vector<T>::iterator Vector<T>::find(const T& element)
{
    typename Vector<T>::iterator it;
    for (it = this->begin(); it != this->end(); ++it) {
        if ((*it) == element) {
            break;
        }
    }
    return it;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::find(const T& element) const
{
    typename Vector<T>::const_iterator it;
    for (it = this->begin(); it != this->end(); ++it) {
        if ((*it) == element) {
            break;
        }
    }
    return it;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::eraseAndDelete(const typename Vector<T>::iterator& it)
{
    delete *it;
    typename Vector<T>::iterator result = this->erase(it);
    return result;
}

template<typename T>
void Vector<T>::operator+=(const Vector<T>& other)
{
    unsigned int count = this->size() < other.size() ? this->size() : other.size();
    for (unsigned int i = 0; i < count; ++i) {
        ref((*this)[i]) += ref(other[i]);
    }
}

template<typename T>
T Vector<T>::min() const
{
    if (this->size() == 0) {
        throw std::logic_error("The vector is empty. Can't call min on it");
    }
    T temp = (*this)[0];
    for (unsigned int i = 1; i < this->size(); ++i) {
        if (ref((*this)[i]) < ref(temp)) {
            temp = (*this)[i];
        }
    }
    return temp;
}

template<typename T>
T Vector<T>::max() const
{
    if (this->size() == 0) {
        throw std::logic_error("The vector is empty. Can't call min on it");
    }
    T temp = (*this)[0];
    for (unsigned int i = 1; i < this->size(); ++i) {
        if (ref((*this)[i]) > ref(temp)) {
            temp = (*this)[i];
        }
    }
    return temp;
}