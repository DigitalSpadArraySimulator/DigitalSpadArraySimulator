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
 * File        : state.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 9 09:29:49 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef STATE_SENSOR_H
#define STATE_SENSOR_H

class Avalanche;
class Particle;
class PDEBehavior;
class ISensorConfiguration;

#include "vector.hh"

/**
 * @class State
 * @brief Abstract class that represents a sensor state
 */
class State{
public:
    /**
     * @brief The different states of a sensor
     */
    enum StateType{
        QUENCHING=0,    ///< The sensor is quenching.
        CHARGING=1,     ///< The sensor is charging.
        READY=2         ///< The sensor is ready.
    };
    
private:
    State();
    State(const State&);
    State& operator=(const State&);
    
    StateType type;
    
protected:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    /**
     * @brief A reference to the Configuration that contains this state.
     */
    ISensorConfiguration const * sensorConfig;
#endif //DOXYGEN_SHOULD_SKIP_THIS
    /**
     * @brief Constructor.
     * 
     * @param type The type of state.
     * @param sensorConfig The configuration used by the sensors.
     */
    State(const StateType& type, ISensorConfiguration const * sensorConfig);
    
    /**
     * @brief Calculate whether or not the particle causes an avalanche.
     * 
     * @param particle The particle that reaches the sensor.
     * @param probElectron The probabilities of an Electron to trigger an avalanche based on the depth in the sensor.
     * @param probHole The probabilities of a Hole to trigger an avalanche based on the depth in the sensor.
     * @param depthProb The depths associated with the probabilities.
     * @return bool
     */
    bool calculateAvalancheProbability(const Particle& particle, 
                                       const Vector<double>& probElectron,
                                       const Vector<double>& probHole,
                                       const Vector<double>& depthProb) const;
    
    /**
    * @brief Calculate the avalanche jitter delay.
    * 
    * @param sensorJitter The sensor jitter.
    * @param sensorDelay The sensor delay.
    * @return double
    */
    double calculateJitterDelay(double sensorJitter, double sensorDelay) const;
    
    /**
     * @brief Sub classes must decide wheither the avalanche is masked or not.
     * 
     * @return bool
     */
    virtual bool createMaskedAvalanche() const = 0;
    
public:
    /**
     * @brief Destructor.
     */
    virtual ~State() {}
    
    /**
     * @brief Check if the conditions to trigger an avalanche are met.
     * 
     * @param particle The particle that hits the sensor.
     * @param overbias The sensor current overbias.
     * @return bool True if an avalanche should be triggered.
     */
    virtual bool testAvalanche(const Particle& particle, const double& overbias) const;
    
    /**
     * @brief Create an avalanche.
     * 
     * @param particle The particle that hits the sensor.
     * 
     * @warning The particle will be given to the Avalanche. Do not delete it by yourself. Delete the avalanche instead.
     * 
     * @return Avalanche* The created avalanche.
     */
    virtual Avalanche* createAvalanche(Particle* particle) const;
    
    /**
     * @brief Get the type of this state.
     * 
     * @return State::StateType
     */
    inline StateType getStateType() const {return type;}
};

#endif //STATE_SENSOR_H