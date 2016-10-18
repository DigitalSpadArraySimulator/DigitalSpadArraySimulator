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
 * File        : isensor_matrix.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "isensor_matrix.hh"

#include <math.h>
#include <stdexcept>

#include "iconfigurable_factory.hh"
#include "isensor.hh"
#include "isensor_factory.hh"
#include "isensor_configuration.hh"
#include "position.hh"
#include "photon.hh"

// Properties that can be passed
const std::string ISensorMatrix::CONTOUR = "contour";
const std::string ISensorMatrix::PITCH = "pitch";
const std::string ISensorMatrix::NB_CELL_X = "ncellx";
const std::string ISensorMatrix::NB_CELL_Y = "ncelly";
const std::string ISensorMatrix::DIMENSION_X = "Dimx";
const std::string ISensorMatrix::DIMENSION_Y = "Dimy";
const std::string ISensorMatrix::DIMENSION_Z = "Dimz";
const std::string ISensorMatrix::CRYSTAL_OFFSET_X = "offsetX";
const std::string ISensorMatrix::CRYSTAL_OFFSET_Y = "offsetY";

// Properties that are generated
const std::string ISensorMatrix::CELL_AREA = "cellArea";
const std::string ISensorMatrix::ACTIVE_AREA = "activeArea";

ISensorMatrix::ISensorMatrix()
: IConfigurable()
, sensors(0)
, sensorFactory(0)
, sensorConfiguration(0)
, sensorConfigurationFactory(0)
, nbSensors(0, 0)
{
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(CONTOUR,               VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(PITCH,                 VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(NB_CELL_X,             VarType::INT));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(NB_CELL_Y,             VarType::INT));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(DIMENSION_X,           VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(DIMENSION_Y,           VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(DIMENSION_Z,           VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(CRYSTAL_OFFSET_X,      VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(CRYSTAL_OFFSET_Y,      VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(CELL_AREA,             VarType::DOUBLE));
    propertiesMappingType.insert(std::pair<std::string, VarType::SUPPORTED_TYPE>(ACTIVE_AREA,           VarType::DOUBLE));
}

ISensorMatrix::~ISensorMatrix()
{
    for (int i = 0; i < nbSensors.x; ++i) {
        for (int j = 0; j < nbSensors.y; ++j) {
            delete sensors[i][j];
        }
        delete[] sensors[i];
    }
    delete[] sensors;
    delete sensorFactory;
    delete sensorConfiguration;
    delete sensorConfigurationFactory;
}

void ISensorMatrix::createSensors()
{
    if (!sensorFactory) {
        throw std::logic_error("There is no ISensorFactory to build the sensors. Call ISensorMatrix::setSensorFactory before this call.");
    }
    if (!sensorConfiguration) {
        throw std::logic_error("The ISensorConfiguration was not previoulsy created. Call ISensorMatrix::initSensorConfiguration before this call.");
    }
    
    sensorFactory->setSensorConfiguration(sensorConfiguration);
    nbSensors = Coordinate2D(getPropertyAs<int>(NB_CELL_X),
                             getPropertyAs<int>(NB_CELL_Y));
    double contour = getPropertyAs<double>(CONTOUR);
    double pitch = getPropertyAs<double>(PITCH);
    
    sensors = new ISensor**[nbSensors.x];
    for (int i = 0; i < nbSensors.x; ++i) {
        sensors[i] = new ISensor*[nbSensors.y];
        for (int j = 0; j < nbSensors.y; ++j) {
            sensors[i][j] = sensorFactory->build(Position2D(contour + pitch/2.0 + pitch * i, contour + pitch/2.0 + pitch * j));
        }
    }
    calculateArea();
}

void ISensorMatrix::calculateArea()
{
    if (!sensorConfiguration) {
        throw std::logic_error("The SensorConfiguration has not been created.");
    }
    
    int nbVertices = sensorConfiguration->getPropertyAs<int>(ISensorConfiguration::NB_VERTICES);
    double radius = sensorConfiguration->getPropertyAs<double>(ISensorConfiguration::RADIUS_TO_SIDES);
    double phi = M_PI / nbVertices;
    double cellArea = nbVertices * radius * radius * tan(phi);
    double activeArea = cellArea * nbSensors.x * nbSensors.y;
    
    setProperty(CELL_AREA, new VarType(cellArea));
    setProperty(ACTIVE_AREA, new VarType(activeArea));
}


ISensor* ISensorMatrix::operator[](const Coordinate2D& coord) const
{
    if (coord.x >= nbSensors.x || coord.x < 0 ||
        coord.y >= nbSensors.y || coord.y < 0) {
#ifdef VERBOSE
        LOG_STREAM(1) << "Out of bounds : " << coord.x << " " << coord.y << std::endl;
#endif //VERBOSE
        throw std::out_of_range("Coordinates refers to a Spad outside of the matrix.");
    }
    
    return sensors[coord.x][coord.y];
}

bool ISensorMatrix::isAbsorbed(Photon& photon) const
{
    bool result = false;
    double contour = getPropertyAs<double>(CONTOUR);
    double pitch = getPropertyAs<double>(PITCH);
    int i = (photon.getPenetrationPoint().x - contour) / pitch;
    int j = (photon.getPenetrationPoint().y - contour) / pitch;
    
    if (i >= 0 && j >= 0 && i < nbSensors.x && j < nbSensors.y) {
        try {
            result = sensors[i][j]->isAbsorbed(photon);
        }
        catch(std::out_of_range) {
            result = false;
#ifdef VERBOSE
            LOG_STREAM(1) << "Photon out of bounds : " << photon.getPenetrationPoint().x << " " << photon.getPenetrationPoint().y << std::endl;
#endif //VERBOSE
        }
        if (result) {
            photon.setSensorCoordinate(Coordinate2D(i, j));
        }
    }
    
    return result;
}


void ISensorMatrix::update(const double& elapsed)
{
    for (int i = 0; i < nbSensors.x; ++i) {
        for (int j = 0; j < nbSensors.y; ++j) {
            sensors[i][j]->update(elapsed);
        }
    }
}

void ISensorMatrix::reset()
{
    for (int i = 0; i < nbSensors.x; ++i) {
        for (int j = 0; j < nbSensors.y; ++j) {
            sensors[i][j]->reset();
        }
    }
}

void ISensorMatrix::setSensorConfigurationFactory(IConfigurableFactory< ISensorConfiguration >* sensorConfigurationFactory)
{
    if (sensorConfiguration && sensors) {
        throw std::logic_error("A ISensorConfiguration was already created and it was already given to every ISensor. You can't change the ISensorConfigurationFactory in this state.");
    }
    if (!sensorConfigurationFactory) {
        throw std::invalid_argument("The given ISensorConfigurationFactory is null.");
    }
    
    if (sensorConfigurationFactory != this->sensorConfigurationFactory) {
        if (this->sensorConfigurationFactory) {
            delete this->sensorConfigurationFactory;
        }
        this->sensorConfigurationFactory = sensorConfigurationFactory;
    }
}

void ISensorMatrix::initSensorConfiguration(const Map<std::string, std::string>& sensorProperties)
{
    if (sensorConfiguration && sensors) {
        throw std::logic_error("A ISensorConfiguration was already created and it was already given to every ISensor. You can't create a new ISensorConfiguration in this state.");
    }
    if (!sensorConfigurationFactory) {
        throw std::logic_error("There is no ISensorConfigurationFactory to build the ISensorConfiguration. Call ISensorMatrix::setSensorConfigurationFactory before this call.");
    }
    sensorConfiguration = sensorConfigurationFactory->build(sensorProperties);
}

void ISensorMatrix::setSensorFactory(ISensorFactory* sensorFactory)
{
    if (!sensorFactory) {
        throw std::invalid_argument("The given ISensorFactory is null.");
    }
    if (sensorFactory != this->sensorFactory) {
        if (this->sensorFactory) {
            delete this->sensorFactory;
        }
        this->sensorFactory = sensorFactory;
    }
}

Position2D ISensorMatrix::getDimension() const
{
    Position2D dimension;
    dimension.x = getPropertyAs<double>(DIMENSION_X);
    dimension.y = getPropertyAs<double>(DIMENSION_Y);
    return dimension;
}

Position2D ISensorMatrix::getCenter() const
{
    Position2D center = getDimension() * 0.5;
    return center;
}

Position2D ISensorMatrix::getCrystalOffset() const
{
    Position2D offset;
    offset.x = getPropertyAs<double>(CRYSTAL_OFFSET_X);
    offset.y = getPropertyAs<double>(CRYSTAL_OFFSET_Y);
    return offset;
}
