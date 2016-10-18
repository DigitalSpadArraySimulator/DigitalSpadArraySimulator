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
 * File        : electric_field_pde.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Mar 8 09:23:22 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef ELECTRIC_FIELD_PDE_SENSOR_H
#define ELECTRIC_FIELD_PDE_SENSOR_H

#include "pde_behavior.hh"

/**
 * @brief PDE generated from electric field values.
 */
class ElectricFieldPDE : public PDEBehavior {
private:
    ElectricFieldPDE();
    ElectricFieldPDE(const ElectricFieldPDE&);
    ElectricFieldPDE& operator=(const ElectricFieldPDE&);
    
    Vector<double> electricField;
    Vector<double> depths;
    double topDepth;
    double dz;
    
public:
    /**
     * @brief Constructor.
     * 
     * @param topDepth The depth of the top part of the sensor.
     * @param electricField The electric field values based on the depth in the sensor.
     * @param depths The depths associated with the electric field values.
     */
    ElectricFieldPDE(const double& topDepth, const Vector<double>& electricField, const Vector<double>& depths);
    
    /**
     * @brief Destructor.
     */
    virtual ~ElectricFieldPDE();
    
    virtual void calculateDepletionZone(const double& overbias, double& depStart, double& depEnd) const  override;
    
    virtual void calculateAvalancheProbabilities(const double& overbias, 
                                                 Vector<double>& electronProb, 
                                                 Vector<double>& holeProb, 
                                                 Vector<double>& probDepth) const  override;
};

#endif //ELECTRIC_FIELD_PDE_SENSOR_H