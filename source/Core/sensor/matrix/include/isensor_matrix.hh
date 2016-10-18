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
 * File        : isensor_matrix.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef I_SENSOR_MATRIX_H
#define I_SENSOR_MATRIX_H

#include "iconfigurable.hh"

#include "coordinate.hh"
#include "position.hh"

template <typename T> class IConfigurableFactory;
template <typename T> class Vector;

class ISensor;
class ISensorConfiguration;
class ISensorFactory;
class ISensorMatrixFactory;
class ISimulator;
class Particle;
class Photon;

/**
 * @brief Derived IConfigurable containing properties for a sensor matrix.
 */
class ISensorMatrix : public IConfigurable {
private:
    friend class ISensorMatrixFactory;
private:
    ISensorMatrix(const ISensorMatrix&);
    ISensorMatrix& operator=(const ISensorMatrix&);
    
protected:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    /**
     * @brief A reference to the simulator that is using this matrix.
     */
    ISimulator const * simulator;
#endif //DOXYGEN_SHOULD_SKIP_THIS
    
    /**
     * @brief A 2D array of sensors.
     */
    ISensor*** sensors;
    
    /**
     * @brief The factory to use to create sensors.
     */
    ISensorFactory* sensorFactory;
    
    /**
     * @brief The number of sensor composing this matrix.
     */
    Coordinate2D nbSensors;
    
    /**
     * @brief The factory to use to create the sensors configuration.
     */
    IConfigurableFactory<ISensorConfiguration>* sensorConfigurationFactory;
    
    /**
     * @brief The configuration shared by all the sensors in this matrix.
     */
    ISensorConfiguration* sensorConfiguration;
    
    /**
     * @brief Calculate the surface of a single sensor and the surface of all the sensors combined.
     * 
     * The calculated data will be added in the properties.
     */
    virtual void calculateArea();
    
    /**
     * @brief Create the sensors in this matrix.
     */
    virtual void createSensors();
    
    /**
     * @brief Set the sensor configuration factory for later uses.
     * 
     * @param sensorConfigurationFactory The sensor configuration factory.
     */
    virtual void setSensorConfigurationFactory(IConfigurableFactory<ISensorConfiguration>* sensorConfigurationFactory);
    
    /**
     * @brief Create the sensor configuration using the factory.
     * 
     * @warning ISensorMatrix::sensorConfigurationFactory must be set before this function.
     * 
     * @param sensorProperties The sensors properties.
     */
    virtual void initSensorConfiguration(const Map<std::string, std::string>& sensorProperties);
    
    /**
     * @brief Set the sensor factory for later uses.
     * 
     * @param sensorFactory The sensor factory.
     */
    virtual void setSensorFactory(ISensorFactory * sensorFactory);

public:
    /**
     * @brief Constructor
     * 
     * Init all the properties mapping type.
     */
    ISensorMatrix();
    
    /**
     * @brief Destructor.
     * 
     * @warning Will delete the sensors, the sensor factory, the sensor configuration and the sensor configuration factory.
     */
    virtual ~ISensorMatrix();
    
    /**
     * @brief Get the sensor located at the given coordinate.
     * 
     * @param coord The Sensor Coordinate.
     * @return ISensor*
     */
    ISensor* operator[](const Coordinate2D& coord) const;
    
    /**
     * @brief Make a bunch of particles walk randomly to reach the sensor depletion zone.
     * 
     * @warning The particles added in the "output" parameter will be removed from the "particles" parameter.
     * 
     * @param[in,out] particles The particles to walk randomly.
     * @param fromTop If true, the particles are in the sensor top part, else, the bottom part.
     * @param[out] output The particles that reached a depletion zone.
     */
    virtual void randomWalk(Vector<Particle*>& particles, const bool& fromTop, Vector<Particle*>& output) const = 0;
    
    /**
     * @brief Try to absorb a photon in the sensors.
     * 
     * @param photon The photon to absorb.
     * @return bool True if the photon was absorbed by a sensor.
     */
    virtual bool isAbsorbed(Photon& photon) const;
    
    /**
     * @brief Sort the particles into three particle groups : top, depletion zone and bottom.
     * 
     * Only the z position of the particles will be used.
     * 
     * @warning The "all" will be emptied by this function to avoid having two pointers on the same Particle.
     * 
     * @param[in,out] all The particles to sort.
     * @param[out] top The particles that are in the top part of a sensor.
     * @param[out] dep The particles that are in the depletion zone of a sensor.
     * @param[out] bottom The particles that are in the bottom part of a sensor.
     */
    virtual void sortByDepth(Vector<Particle*>& all, Vector<Particle*>& top, Vector<Particle*>& dep, Vector<Particle*>& bottom) = 0;
    
    /**
     * @brief Update every sensor.
     * 
     * @param elapsed The time elapsed since last update.
     */
    virtual void update(const double& elapsed);
    
    /**
     * @brief Reset every sensor.
     */
    virtual void reset();
    
    /**
     * @brief Get the number of sensor in X and Y of this matrix.
     * 
     * @return const Coordinate2D&
     */
    inline const Coordinate2D& getNbSensors() const {return nbSensors;}
    
    /**
     * @brief Get the matrix dimension (X, Y) (\f$\mu\text{m}\f$)
     * 
     * @return Position2D
     */
    Position2D getDimension() const;
    
    /**
     * @brief Get the matrix center (X, Y) (\f$\mu\text{m}\f$)
     * 
     * @return Position2D
     */
    Position2D getCenter() const;
    
    /**
     * @brief Get the matrix crystal offset (X, Y) (\f$\mu\text{m}\f$)
     * 
     * @return Position2D
     */
    Position2D getCrystalOffset() const;
    
    /**
     * @brief Get the sensor configuration shared by every sensor in the matrix.
     * 
     * @return const ISensorConfiguration&
     */
    inline const ISensorConfiguration& getSensorConfiguration() const {return *sensorConfiguration;}
    
public:
    /**
     * @brief Width of the outer margin. (\f$\mu\text{m}\f$)
     * 
     * PropertyName: "contour"
     * 
     * PropertyType: double
     */
    static const std::string CONTOUR;
    
    /**
     * @brief Distance between two sensor's center. (\f$\mu\text{m}\f$)
     * 
     * PropertyName: "pitch"
     * 
     * PropertyType: double
     */
    static const std::string PITCH;
    
    /**
     * @brief Number of sensors in a line.
     * 
     * PropertyName: "ncellx"
     * 
     * PropertyType: int
     */
    static const std::string NB_CELL_X;
    
    /**
     * @brief Number of sensors in a row.
     * 
     * PropertyName: "ncelly"
     * 
     * PropertyType: int
     */
    static const std::string NB_CELL_Y;
    
    /**
     * @brief Total width of the matrix. (\f$\mu\text{m}\f$)
     * 
     * PropertyName: "Dimx"
     * 
     * PropertyType: double
     */
    static const std::string DIMENSION_X;
    
    /**
     * @brief Total height of the matrix. (\f$\mu\text{m}\f$)
     * 
     * PropertyName: "Dimy"
     * 
     * PropertyType: double
     */
    static const std::string DIMENSION_Y;
    
    /**
     * @brief Total depth of the matrix. (\f$\mu\text{m}\f$)
     * 
     * PropertyName: "Dimz"
     * 
     * PropertyType: double
     */
    static const std::string DIMENSION_Z;
    
    /**
     * @brief The offset of the crystal in x. (\f$\mu\text{m}\f$)
     * 
     * PropertyName: "offsetX"
     * 
     * PropertyType: double
     */
    static const std::string CRYSTAL_OFFSET_X;
    
    /**
     * @brief The offset of the crystal in y. (\f$\mu\text{m}\f$)
     * 
     * PropertyName: "offsetY"
     * 
     * PropertyType: double
     */
    static const std::string CRYSTAL_OFFSET_Y;
    
    /**
     * @brief The area covered by one sensor. (\f$\mu\text{m}^2\f$)
     * 
     * @warning This property is calculated by the ISensorMatrix.
     * 
     * PropertyName: "cellArea"
     * 
     * PropertyType: double
     */
    static const std::string CELL_AREA;
    
    /**
     * @brief The area covered by all the sensor. (\f$\mu\text{m}^2\f$)
     * 
     * @warning This property is calculated by the ISensorMatrix.
     * 
     * PropertyName: "activeArea"
     * 
     * PropertyType: double
     */
    static const std::string ACTIVE_AREA;
};

#endif //I_SENSOR_MATRIX_H