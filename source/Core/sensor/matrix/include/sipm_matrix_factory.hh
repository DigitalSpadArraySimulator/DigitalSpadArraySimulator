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
 * File        : sipm_matrix_factory.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Apr 13 11:30:25 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef SIPM_MATRIX_FACTORY_H
#define SIPM_MATRIX_FACTORY_H

#include "spad_matrix_factory.hh"

/**
 * @brief Derived SpadMatrixFactory that creates a SipmMatrix instead of a SpadMatrix.
 */
class SipmMatrixFactory : public SpadMatrixFactory {
private:
    SipmMatrixFactory(const SipmMatrixFactory&);
    SipmMatrixFactory& operator=(const SipmMatrixFactory&);
    
public:
    /**
     * @brief Constructor.
     */
    SipmMatrixFactory();
    
    /**
     * @brief Destructor.
     */
    virtual ~SipmMatrixFactory();
    
    virtual ISensorMatrix* build(const Map<std::string, std::string>& matrixProperties, 
                                 const Map<std::string, std::string>& sensorProperties) override;
};

#endif //SIPM_MATRIX_FACTORY_H