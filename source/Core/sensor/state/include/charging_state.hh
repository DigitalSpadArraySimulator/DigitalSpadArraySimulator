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
 * File        : charging_state.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Mar 15 10:13:19 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef CHARGING_STATE_SENSOR_H
#define CHARGING_STATE_SENSOR_H

#include "state.hh"

/**
 * @brief In this state, the sensor can quench. 
 */
class ChargingState : public State {
private:
    ChargingState(const ChargingState&);
    ChargingState& operator=(const ChargingState&);
    
public:
    /**
     * @brief Constructor.
     */
    ChargingState(ISensorConfiguration const * sensorConfig);
    
    /**
     * @brief Destructor.
     */
    virtual ~ChargingState() {}
    
protected:
    /**
     * @brief Check if the conditions to trigger an avalanche are met.
     * 
     * @param particle The particle that hits the Spad.
     * @param overbias The Spad current overbias.
     * @return bool True if an avalanche should be triggered.
     */
    virtual bool testAvalanche(const Particle& particle, const double& overbias) const override;
    
    /**
     * @brief Avalanches occuring, while spad is in this state, are never masked.
     * 
     * @return bool false.
     */
    inline virtual bool createMaskedAvalanche() const  override {return false;}
};

#endif //CHARGING_STATE_SENSOR_H