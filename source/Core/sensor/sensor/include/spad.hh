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
 * File        : spad.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Feb 26 09:44:39 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef SPAD_SENSOR_H
#define SPAD_SENSOR_H

#include "isensor.hh"

class Avalanche;
class SpadFactory;
class Polygon;
class Photon;
class Particle;
class VarType;
class PDEBehavior;
class SpadConfiguration;

/**
 * @brief Derived ISensor representing a single photon avalanche diode (spad).
 */
class Spad : public ISensor{
private:
    friend class SpadFactory;
    
private:
    Spad(const Spad&);
    Spad& operator=(const Spad&);
    
protected:
    /**
     * @brief The current value of the overbias.
     */
    double overbias;
    
public:
    /**
     * @brief Constructor.
     */
    Spad();
    
    /**
     * @brief Destructor.
     */
    virtual ~Spad();
    
    virtual bool isAbsorbed(const Photon& photon) const  override;
    virtual bool randomWalk(Particle& particle, 
                            const double& meanLifetime, 
                            const bool& fromTop, 
                            const double& tau, 
                            const double& scalingFactor) const  override;
    virtual void update(const double& elapsed)  override;
    virtual Avalanche* trigger(Particle* particle)  override;
    virtual void reset() override;
    
protected:
    /**
     * @brief Set the state to quenching
     */
    virtual void quench();
};

#endif //SPAD_SENSOR_H