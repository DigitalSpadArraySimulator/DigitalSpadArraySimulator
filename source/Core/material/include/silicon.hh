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
 * File        : silicon.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 3 14:30:27 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef SILICON_MATERIAL_H
#define SILICON_MATERIAL_H

#include "isilicon.hh"

class AbsorptionBehavior;
class Photon;
class SiliconFactory;
class VarType;

/**
 * @brief Class containing information of the silicon used in a simulation.
 */
class Silicon : public ISilicon {
private:
    friend class SiliconFactory;
private:
    Silicon(const Silicon&);
    Silicon& operator=(const Silicon&);
    
public:
    /**
     * @brief Constructor.
     */
    Silicon();
    
    /**
     * @brief Destructor.
     */
    virtual ~Silicon();
};

#endif //SILICON_MATERIAL_H