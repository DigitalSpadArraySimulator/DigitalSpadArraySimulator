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
 * File        : isensor_configuration.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef I_SENSOR_CONFIGURATION_H
#define I_SENSOR_CONFIGURATION_H

#include "iconfigurable.hh"

#include "state.hh"

template <typename T> class Vector;
class PDEBehavior;
class ISimulator;

/**
 * @brief Derived IConfigurable that contains the properties need for the configuration of all the sensors in a matrix.
 */
class ISensorConfiguration : public IConfigurable {
private:
    ISensorConfiguration(const ISensorConfiguration&);
    ISensorConfiguration& operator=(const ISensorConfiguration&);
    
protected:
    /**
     * @brief Constructor
     * 
     * Init all the properties mapping type.
     */
    ISensorConfiguration();
    
    /**
     * @brief The available states for the sensors.
     */
    Map<State::StateType, State*> states;
    
    /**
     * @brief The pde behavior used by the sensors.
     */
    PDEBehavior const * pde;
    
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    /**
     * @brief A reference to the simulator containing the matrix.
     */
    ISimulator const * simulator;
#endif //DOXYGEN_SHOULD_SKIP_THIS
    
    /**
     * @brief The probabilities of an electron to triggers an avalanche, when the sensor is in ready state, based on the depth in the sensor.
     */
    Vector<double> readyProbE;
    
    /**
     * @brief The probabilities of a hole to triggers an avalanche, when the sensor is in ready state, based on the depth in the sensor.
     */
    Vector<double> readyProbH;
    
    /**
     * @brief The depths associated with the probabilities.
     */
    Vector<double> readyDepths;
    
public:
    /**
     * @brief Destructor.
     */
    virtual ~ISensorConfiguration();
    
    /**
     * @brief Get a state based on it's type.
     * 
     * @param stateType The state type.
     * @return State*
     */
    virtual State* getState(const State::StateType& stateType) const;
    
    /**
     * @brief Get the pde shared by all the sensors in the matrix.
     * 
     * @return const PDEBehavior&
     */
    inline virtual const PDEBehavior& getPDE() const {return *pde;}
    
    /**
     * @brief Get the reference to the simulator.
     * 
     * @return const ISimulator*
     */
    inline virtual ISimulator const * getSimulator() const {return simulator;}
    
    /**
     * @brief Get the probabilities of an electron to triggers an avalanche, when the sensor is in ready state, based on the depth in the sensor.
     * 
     * @return const Vector< double >&
     */
    inline virtual const Vector<double>& getReadyProbE() const {return readyProbE;}
    
    /**
     * @brief Get the probabilities of a Hole to triggers an avalanche, when the sensor is in ready state, based on the depth in the sensor.
     * 
     * @return const Vector< double >&
     */
    inline virtual const Vector<double>& getReadyProbH() const {return readyProbH;}
    
    /**
     * @brief Get the depths associated with the probabilities.
     * 
     * @return const Vector< double >&
     */
    inline virtual const Vector<double>& getReadyDepths() const {return readyDepths;}
    
public:
    /**
     * @brief The number of vertices in the sensor polygon.
     * 
     * Ex: square = 4
     * 
     * PropertyName: "vertices"
     * 
     * PropertyType: int
     */
    static const std::string NB_VERTICES;
    
    /**
     * @brief Shortest distance between the sensor center and one side.
     * 
     * PropertyName: "radius"
     * 
     * PropertyType: double
     */
    static const std::string RADIUS_TO_SIDES;
    
    /**
     * @brief The distance between the sensor center and a vertex. (\f$\mu\text{m}\f$)
     * 
     * @warning This property is calculated by the ISensorFactory.
     * 
     * PropertyName: "correctedRadius"
     * 
     * PropertyType: double
     */
    static const std::string RADIUS_TO_VERTICES;
    
    /**
     * @brief The angle between each vertex. (radian)
     * 
     * @warning This property is calculated by the ISensorFactory.
     * 
     * PropertyName: "angle"
     * 
     * PropertyType: double
     */
    static const std::string ANGLE;
};

#endif //I_SENSOR_CONFIGURATION_H