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
 * File        : map.hpp
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 3 14:30:27 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


template <typename keyT, typename valueT>
void Map<keyT, valueT>::clearAndDeleteValues()
{
    typename Map<keyT, valueT>::iterator it;
    for (it = this->begin(); it != this->end();) {
        it = this->eraseAndDeleteValue(it);
    }
}

template <typename keyT, typename valueT>
void Map<keyT, valueT>::clearAndDeleteKeys()
{
    typename Map<keyT, valueT>::iterator it;
    for (it = this->begin(); it != this->end();) {
        it = this->eraseAndDeleteKey(it);
    }
}

template <typename keyT, typename valueT>
void Map<keyT, valueT>::clearAndDeletePairs() 
{
    typename Map<keyT, valueT>::iterator it;
    for (it = this->begin(); it != this->end();) {
        it = this->eraseAndDeletePair(it);
    }
}

template <typename keyT, typename valueT>
typename Map<keyT, valueT>::iterator Map<keyT, valueT>::eraseAndDeleteValue(const typename Map<keyT, valueT>::iterator& it)
{
    delete it->second;
    return this->erase(it);
}

template <typename keyT, typename valueT>
typename Map<keyT, valueT>::iterator Map<keyT, valueT>::eraseAndDeleteKey(const typename Map<keyT, valueT>::iterator& it)
{
    delete it->first;
    return this->erase(it);
}

template <typename keyT, typename valueT>
typename Map<keyT, valueT>::iterator Map<keyT, valueT>::eraseAndDeletePair(const typename Map<keyT, valueT>::iterator& it)
{
    delete it->first;
    delete it->second;
    return this->erase(it);
}
