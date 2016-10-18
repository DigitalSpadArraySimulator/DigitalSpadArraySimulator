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
 * File        : pde_behavior.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 16:57:33 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef PDE_BEHAVIOR_SENSOR_H
#define PDE_BEHAVIOR_SENSOR_H

#include "vector.hh"

/**
 * @brief Abstract class used to calculate the depletion zone and the avalanche probabilities.
 */
class PDEBehavior{
private:
    PDEBehavior();
    PDEBehavior(const PDEBehavior&);
    PDEBehavior& operator=(const PDEBehavior&);
    
    bool fullAbsorption;
    
protected:
    /**
     * @brief Constructor.
     * 
     * @param fullAbsorption If false, only the penetration point of the photon will be check during the absorption.
     */
    PDEBehavior(const bool& fullAbsorption);
    
public:
    /**
     * @brief Destructor.
     */
    virtual ~PDEBehavior() {}
    
    /**
     * @brief Check if the absorption condition should be based only on the penetration point or on the absorption point to.
     * 
     * @return bool false for the penetration point only.
     */
    virtual inline bool doFullAbsorption() { return fullAbsorption; }
    
    /**
     * @brief Calculate the depletion zone limits based on the sensor overbias.
     * 
     * @param overbias The overbias.
     * @param[out] depStart The begining of the depletion zone in z.
     * @param[out] depEnd The end of the depletion zone in z.
     */
    virtual void calculateDepletionZone(const double& overbias, double& depStart, double& depEnd) const = 0;
    
    /**
     * @brief Calculate the probabilities to create an avalanche based on the overbias.
     * 
     * @param overbias The overbias.
     * @param[out] electronProb The probabilities for an electron to create an avalanche depending on it's depth.
     * @param[out] holeProb The probabilities for a hole to create an avalanche depending on it's depth.
     * @param[out] probDepth The depths associated with the probabilities.
     */
    virtual void calculateAvalancheProbabilities(const double& overbias, 
                                                 Vector<double>& electronProb, 
                                                 Vector<double>& holeProb, 
                                                 Vector<double>& probDepth) const = 0;
};

#endif //PDE_BEHAVIOR_SENSOR_H