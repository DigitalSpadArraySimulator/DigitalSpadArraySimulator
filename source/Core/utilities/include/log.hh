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
 * File        : log.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Mon Mar 21 12:59:55 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef LOG_UTILITIES_H
#define LOG_UTILITIES_H
#include <iostream>
#include <streambuf>
#include "build_config.hh"

extern int VERBOSE_MAX;

/**
 * @brief A buffer that do nothing.
 */
class NullBuffer : public std::streambuf {
public:
    /**
     * @brief Override base function to do nothing.
     */
    virtual inline int overflow(int c) {return c;}
};

extern NullBuffer nullBuffer;
extern std::ostream nullStream;
extern std::ostream *pLogStream, *pNullStream;

#ifdef VERBOSE
#define LOG(message, level) if((level) <= VERBOSE_MAX) {std::cout << (message) << std::endl;}
#define LOG_STREAM(level) *((level) <= VERBOSE_MAX ? pLogStream : pNullStream)
#else
#define LOG(message, level)
#define LOG_STREAM(level) nullStream
#endif //VERBOSE

#endif //LOG_UTILITIES_H