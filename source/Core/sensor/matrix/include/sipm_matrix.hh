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
 * File        : sipm_matrix.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Apr 13 11:30:25 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef SIPM_MATRIX_H
#define SIPM_MATRIX_H

#include "spad_matrix.hh"

/**
 * @brief Derived SpadMatrix that uses Sipm instead of Spad.
 */
class SipmMatrix : public SpadMatrix {
private:
    SipmMatrix(const SipmMatrix&);
    SipmMatrix& operator=(const SipmMatrix&);
    
public:
    /**
     * @brief Constructor.
     */
    SipmMatrix();
    
    /**
     * @brief Destructor.
     */
    virtual ~SipmMatrix();
    
    virtual void reset() override;
};

#endif //SIPM_MATRIX_H