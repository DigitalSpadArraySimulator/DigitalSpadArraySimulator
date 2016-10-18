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
 * File        : ready_state.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 9 09:29:49 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef READY_STATE_SENSOR_H
#define READY_STATE_SENSOR_H

#include "state.hh"

/**
 * @brief In this state, the sensor can quench. 
 */
class ReadyState : public State {
private:
    ReadyState();
    ReadyState(const ReadyState&);
    ReadyState& operator=(const ReadyState&);
    
public:
    /**
     * @brief Create a ReadyState
     */
    ReadyState(ISensorConfiguration const * sensorConfig);
    
    /**
     * @brief Destructor
     */
    virtual ~ReadyState() {}
    
protected:
    /**
     * @brief Avalanches occuring, while the sensor is in this state, are never masked.
     * 
     * @return bool false.
     */
    inline virtual bool createMaskedAvalanche() const  override {return false;}
};

#endif //READY_STATE_SENSOR_H