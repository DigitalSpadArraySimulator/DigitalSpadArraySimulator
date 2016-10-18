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
 * File        : spad_matrix.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Feb 26 09:44:39 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef SPAD_MATRIX_SENSOR_H
#define SPAD_MATRIX_SENSOR_H

#include "isensor_matrix.hh"

#include "coordinate.hh"
#include "map.hh"
#include <string>
#include "vector.hh"

class Spad;
class Particle;
class Photon;
class VarType;
class SpadMatrixFactory;

/**
 * @brief A Matrix containing Spad.
 */
class SpadMatrix : public ISensorMatrix {
private:
    friend class SpadMatrixFactory;
private:
    SpadMatrix(const SpadMatrix&);
    SpadMatrix& operator=(const SpadMatrix&);
    
public:
    /**
     * @brief Constructor.
     */
    SpadMatrix();
    
    /**
     * @brief Destructor.
     */
    virtual ~SpadMatrix();
    
    virtual void randomWalk(Vector<Particle*>& particles, const bool& fromTop, Vector<Particle*>& output) const override;
    virtual void sortByDepth(Vector<Particle*>& all, Vector<Particle*>& top, Vector<Particle*>& dep, Vector<Particle*>& bottom) override;
};

#endif //SPAD_MATRIX_SENSOR_H