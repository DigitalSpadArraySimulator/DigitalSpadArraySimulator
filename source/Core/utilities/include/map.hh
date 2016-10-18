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
 * File        : map.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 2 15:19:04 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef MAP_UTILITIES_H
#define MAP_UTILITIES_H

#include <map>

/**
 * @brief Specialized map that can delete key and/or value if wanted
 */
template<typename keyT, typename valueT>
class Map : public std::map<keyT, valueT>{
public:
    /**
     * @brief Clear the map and delete only the values
     * @see http://www.cplusplus.com/reference/map/map/clear/
     */
    void clearAndDeleteValues();
    /**
     * @brief Clear the map and delete only the keys
     * @see http://www.cplusplus.com/reference/map/map/clear/
     */
    void clearAndDeleteKeys();
    /**
     * @brief Clear the map and delete both keys and values
     * @see http://www.cplusplus.com/reference/map/map/clear/
     */
    void clearAndDeletePairs();
    
    /**
     * @brief Erase the pair pointed by the iterator and delete only the value
     * @param it iterator pointing to the pair to erase
     * @return Map< keyT, valueT >::iterator an iterator pointing to the pair next to the erased one
     * @see http://www.cplusplus.com/reference/map/map/erase/
     */
    typename Map<keyT, valueT>::iterator eraseAndDeleteValue(const typename Map<keyT, valueT>::iterator& it);
    /**
     * @brief Erase the pair pointed by the iterator and delete only the key
     * @param it iterator pointing to the pair to erase
     * @return Map< keyT, valueT >::iterator an iterator pointing to the pair next to the erased one
     * @see http://www.cplusplus.com/reference/map/map/erase/
     */
    typename Map<keyT, valueT>::iterator eraseAndDeleteKey(const typename Map<keyT, valueT>::iterator& it);
    /**
     * @brief .Erase the pair pointed by the iterator and delete both value and key
     * @param it iterator pointing to the pair to erase
     * @return Map< keyT, valueT >::iterator an iterator pointing to the pair next to the erased one
     * @see http://www.cplusplus.com/reference/map/map/erase/
     */
    typename Map<keyT, valueT>::iterator eraseAndDeletePair(const typename Map<keyT, valueT>::iterator& it);
};

#include "map.hpp"

#endif //MAP_UTILITIES_H