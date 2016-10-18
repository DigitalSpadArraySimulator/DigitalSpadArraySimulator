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
 * File        : quenching_state.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 9 09:29:49 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef QUENCHING_STATE_SENSOR_H
#define QUENCHING_STATE_SENSOR_H

#include "state.hh"

/**
 * @brief In this state, the sensor can't quench. 
 * 
 * All the generated avalanches are considered masked since they never actually happened.
 */
class QuenchingState : public State {
private:
    QuenchingState(const QuenchingState&);
    QuenchingState& operator=(const QuenchingState&);
    
public:
    /**
     * @brief Constructor.
     */
    QuenchingState(ISensorConfiguration const * sensorConfig);
    
    /**
     * @brief Destructor.
     */
    virtual ~QuenchingState() {}
protected:
    /**
     * @brief Avalanches occuring, while the sensor is in this state, are always masked.
     * 
     * @return bool true.
     */
    inline virtual bool createMaskedAvalanche() const  override {return true;}
};

#endif //QUENCHING_STATE_SENSOR_H