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
 * File        : junction_pde.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 16:57:33 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef JUNCTION_PDE_SENSOR_H
#define JUNCTION_PDE_SENSOR_H

#include "pde_behavior.hh"

class ISilicon;

/**
 * @brief The default PDE that will be generated from sensor properties.
 */
class JunctionPDE : public PDEBehavior {
private:
    JunctionPDE();
    JunctionPDE(const JunctionPDE&);
    JunctionPDE& operator=(const JunctionPDE&);
    
    ISilicon const * silicon;
    double temperature;
    double breakdownTension;
    double topDepth;
    
    void calculateElectricField(const double& overbias, Vector<double>& electricField, Vector<double>& depths) const;
    
public:
    /**
     * @brief Create a junction PDE.
     * 
     * @param silicon A reference to the silicon used in this simulation.
     * @param temperature The temperature of the sensor.
     * @param breakdownTension The breakdown tension.
     * @param topDepth The depth of the top part of the sensor.
     */
    JunctionPDE(ISilicon const * silicon, const double& temperature, const double& breakdownTension, const double& topDepth);
    
    /**
     * @brief Desctructor.
     * 
     * @warning Will not delete the silicon.
     */
    virtual ~JunctionPDE();
    
    virtual void calculateDepletionZone(const double& overbias, double& depStart, double& depEnd) const  override;
    
    virtual void calculateAvalancheProbabilities(const double& overbias, 
                                                 Vector<double>& electronProb, 
                                                 Vector<double>& holeProb, 
                                                 Vector<double>& probDepth) const  override;
}; 

#endif //JUNCTION_PDE_SENSOR_H