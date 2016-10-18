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
 * File        : spad_matrix_factory.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Feb 26 09:44:39 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef SPAD_MATRIX_FACTORY_SENSOR_H
#define SPAD_MATRIX_FACTORY_SENSOR_H

class SpadMatrix;
class Coordinate2D;

#include <string>

#include "isensor_matrix_factory.hh"
#include "map.hh"

/**
 * @brief Derived ISensorMatrixFactory that creates and configures a SpadMatrix.
 */
class SpadMatrixFactory : public ISensorMatrixFactory{
private:
    SpadMatrixFactory(const SpadMatrixFactory&);
    SpadMatrixFactory& operator=(const SpadMatrixFactory&);

public:
    /**
     * @brief Constructor.
     */
    SpadMatrixFactory();
    
    /**
     * @brief Destructor.
     */
    virtual ~SpadMatrixFactory();
    
    virtual ISensorMatrix* build(const Map<std::string, std::string>& matrixProperties, 
                                 const Map<std::string, std::string>& sensorProperties) override;
};

#endif //SPAD_MATRIX_FACTORY_SENSOR_H