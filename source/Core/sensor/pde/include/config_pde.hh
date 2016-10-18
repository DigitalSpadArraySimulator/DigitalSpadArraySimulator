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
 * File        : config_pde.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 16:57:33 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef CONFIG_PDE_SENSOR_H
#define CONFIG_PDE_SENSOR_H

#include "pde_behavior.hh"

/**
 * @brief PDE generated from two parameters.
 * 
 * With this PDE, the whole sensor is considered as the depletion zone.
 * 
 * The absorption condition is only done on the sensor surface penetration point.
 * 
 * The random walk is not needed since all the sensor is a depletion zone.
 */
class ConfigPDE : public PDEBehavior{
private:
    ConfigPDE();
    ConfigPDE(const ConfigPDE&);
    ConfigPDE& operator=(const ConfigPDE&);
    
    double pdeA;
    double pdeB;
    double spadDepth;
    
public:
    /**
     * @brief Constructor.
     * 
     * \f[pde=A*(1-e^{-B*\text{overbias}})\f]
     * 
     * @param pdeA \f$A\f$.
     * @param pdeB \f$B\f$.
     * @param spadDepth The total SPAD depth.
     */
    ConfigPDE(const double& pdeA, const double& pdeB, const double& spadDepth);
    
    /**
     * @brief Destructor.
     */
    virtual ~ConfigPDE() {}
    
    virtual void calculateDepletionZone(const double& overbias, double& depStart, double& depEnd) const  override;
    
    virtual void calculateAvalancheProbabilities(const double& overbias, 
                                                 Vector<double>& electronProb, 
                                                 Vector<double>& holeProb, 
                                                 Vector<double>& probDepth) const  override;
};

#endif //CONFIG_PDE_SENSOR_H