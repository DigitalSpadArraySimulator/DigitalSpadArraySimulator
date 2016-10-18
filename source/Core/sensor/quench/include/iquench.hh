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
 * File        : iquench.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef I_QUENCH_H
#define I_QUENCH_H

#include "iconfigurable.hh"

/**
 * @brief Abstract class containing all the quench properties mapping type.
 */
class IQuench : public IConfigurable {
private:
    friend class IQuenchFactory;
private:
    IQuench(const IQuench&);
    IQuench& operator=(const IQuench&);
    
protected:
    /**
     * @brief Constructor
     * 
     * Init all the properties mapping type.
     */
    IQuench();
    
public:
    /**
     * @brief Destructor.
     */
    virtual ~IQuench() {}
    
    /**
     * @brief Time before the sensor is charged after the dead time. (ns)
     * 
     * PropertyName: "RechargeDelay"
     * 
     * PropertyType: double
     */
    static const std::string RECHARGE_DELAY;
    
    /**
     * @brief Time after an avalench when the sensor can't listen to a new event. (ns)
     * 
     * PropertyName: "Dead_time"
     * 
     * PropertyType: double
     */
    static const std::string DEAD_TIME;
    
    /**
     * @brief Time needed by the electronic component to detect an event while charging. (ns)
     * 
     * PropertyName: "Reset_time"
     * 
     * PropertyType: double
     */
    static const std::string RESET_TIME;
    
    /**
     * @brief Maximum time of a PET event. (ns)
     * 
     * PropertyName: "Max_event_time"
     * 
     * PropertyType: double
     */
    static const std::string MAX_EVENT_TIME;
};

#endif //I_QUENCH_H