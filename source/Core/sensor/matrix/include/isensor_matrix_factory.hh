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
 * File        : isensor_matrix_factory.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef I_SENSOR_MATRIX_FACTORY_H
#define I_SENSOR_MATRIX_FACTORY_H

#include "iconfigurable_factory.hh"

class ISensorFactory;
class ISensorMatrix;
class ISimulator;
class ISensorConfiguration;

/**
 * @brief Derived IConfigurableFactory specialized for creating ISensorMatrix.
 */
class ISensorMatrixFactory : public IConfigurableFactory<ISensorMatrix>{
private:
    ISensorMatrixFactory(const ISensorMatrixFactory&);
    ISensorMatrixFactory& operator=(const ISensorMatrixFactory&);
    
protected:
    /**
     * @brief Constructor.
     */
    ISensorMatrixFactory();
    
    #ifndef DOXYGEN_SHOULD_SKIP_THIS
    /**
     * @brief A reference to the simulator that will contain the sensor matrix.
     */
    ISimulator const * simulator;
    #endif //DOXYGEN_SHOULD_SKIP_THIS
    
    /**
     * @brief The factory the sensor matrix will use to create sensors.
     */
    ISensorFactory* sensorFactory;
    
    /**
     * @brief The factory the sensor matrix will use to create the sensors' configuration.
     */
    IConfigurableFactory<ISensorConfiguration>* sensorConfigurationFactory;
    
    /**
     * @brief Set the simulator in the matrix.
     * 
     * @warning ISensorMatrixFactory::simulator must be set before calling this function.
     * 
     * @param sensorMatrix The matrix.
     */
    virtual void setSimulator(ISensorMatrix* sensorMatrix);
    
    /**
     * @brief Set the sensor factory in the matrix.
     * 
     * @warning ISensorMatrixFactory::sensorFactory must be set before calling this function.
     * 
     * @param sensorMatrix The matrix.
     */
    virtual void setSensorFactory(ISensorMatrix* sensorMatrix);
    
    /**
     * @brief Set the sensor configruation factory in the matrix.
     * 
     * @warning ISensorMatrixFactory::sensorConfigurationFactory must be set before calling this function.
     * 
     * @param sensorMatrix The matrix.
     */
    virtual void setSensorConfigurationFactory(ISensorMatrix* sensorMatrix);
    
public:
    /**
     * @brief Destructor.
     * 
     * @warning Will not delete ISensorMatrixFactory::simulator, ISensorMatrixFactory::sensorFactory, ISensorMatrixFactory::sensorConfigurationFactory.
     */
    virtual ~ISensorMatrixFactory();
    
    /**
     * @brief Set the simulator to be passed to the matrix.
     * 
     * @param simulator The simulator.
     */
    virtual void setSimulator(ISimulator const * simulator);
    
    /**
     * @brief Set the sensor factory to be passed to the matrix.
     * 
     * @param sensorFactory The sensor factory.
     */
    virtual void setSensorFactory(ISensorFactory* sensorFactory);
    
    /**
     * @brief Set the sensor configuration factory to be passed to the matrix.
     * 
     * @param sensorConfigurationFactory The sensor configuration factory.
     */
    virtual void setSensorConfigurationFactory(IConfigurableFactory<ISensorConfiguration>* sensorConfigurationFactory);
    
    /**
     * @brief Build a sensor matrix.
     * 
     * @warning Only redirect the call to ISensorMatrix::build with an empty map for sensors' properties.
     * 
     * @param properties The matrix properties.
     * @return ISensorMatrix*
     */
    virtual ISensorMatrix* build(const Map<std::string, std::string>& properties) override;
    
    /**
     * @brief Build a sensor matrix.
     * 
     * @param matrixProperties The matrix properties.
     * @param sensorProperties The sensors properties.
     * @return ISensorMatrix*
     */
    virtual ISensorMatrix* build(const Map<std::string, std::string>& matrixProperties,
                                 const Map<std::string, std::string>& sensorProperties) = 0;
    
};

#endif //I_SENSOR_MATRIX_FACTORY_H