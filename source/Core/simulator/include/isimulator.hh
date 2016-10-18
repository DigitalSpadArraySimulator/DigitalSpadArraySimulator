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
 * File        : isimulator.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef I_SIMULATOR_H
#define I_SIMULATOR_H

#include <string>

template <typename T> class IConfigurableFactory;
template <typename T> class Vector;
template <typename T1, typename T2> class Map;

class Avalanche;
class IQuench;
class ISensorMatrix;
class ISensorMatrixFactory;
class ISilicon;
class ISiliconFactory;
class Particle;
class Photon;

/**
 * @brief Abstract class for Simulator.
 */
class ISimulator {
private:
    ISimulator(const ISimulator&);
    ISimulator& operator=(const ISimulator&);
    
protected:
    /**
     * @brief Constructor.
     */
    ISimulator();
    
    /**
     * @brief The quench properties used in this simulation.
     */
    IQuench* quench;
    
    /**
     * @brief The sensor matrix used in this simulation.
     */
    ISensorMatrix* matrix;
    
    /**
     * @brief The silicon properties used in this simulation.
     */
    ISilicon* silicon;
    
    /**
     * @brief The factory that will be used to build the quench properties.
     */
    IConfigurableFactory<IQuench>* quenchFactory;
    
    /**
     * @brief The factory that will be used to build the sensor matrix.
     */
    ISensorMatrixFactory* matrixFactory;
    
    /**
     * @brief The factory that will be used to build the silicon properties.
     */
    ISiliconFactory* siliconFactory;
    
public:
    /**
     * @brief Destructor.
     * 
     * @warning Will delete the matrix, quench, silicon and their factory.
     */
    virtual ~ISimulator();
    
    /**
     * @brief The simulation's quench properties.
     * 
     * @return const IQuench*
     */
    inline IQuench const * getQuench() const {return quench;}
    
    /**
     * @brief The simulation's sensor matrix.
     * 
     * @return const ISensorMatrix*
     */
    inline ISensorMatrix const * getSensorMatrix() const {return matrix;}
    
    /**
     * @brief The simulation's silicon properties.
     * 
     * @return const ISilicon*
     */
    inline ISilicon const * getSilicon() const {return silicon;}
    
    /**
     * @brief Set the factory to use when building the quench properties.
     * 
     * @warning You need to call this before ISimulator::init is called.
     * 
     * @param quenchFactory The factory to use.
     */
    virtual void setQuenchFactory(IConfigurableFactory<IQuench>* quenchFactory);
    
    /**
     * @brief Set the factory to use when building the sensor matrix.
     * 
     * @warning You need to call this before ISimulator::init is called.
     * 
     * @param matrixFactory The factory to use.
     */
    virtual void setSensorMatrixFactory(ISensorMatrixFactory* matrixFactory);
    
    /**
     * @brief Set the factory to use when building the silicon properties.
     * 
     * @warning You need to call this before ISimulator::init is called.
     * 
     * @param siliconFactory The factory to use.
     */
    virtual void setSiliconFactory(ISiliconFactory* siliconFactory);
    
    /**
     * @brief Initialize every components in the SpadMatrix
     * 
     * @param siliconProperties The silicon properties <PropertyName, PropertyValue>
     * @param quenchProperties The quench properties <PropertyName, PropertyValue>
     * @param spadProperties The spad properties <PropertyName, PropertyValue>
     * @param matrixProperties The SpadMatrix properties <PropertyName, PropertyValue>
     */
    virtual void init(const Map<std::string, std::string>& siliconProperties,
                      const Map<std::string, std::string>& quenchProperties,
                      const Map<std::string, std::string>& spadProperties,
                      const Map<std::string, std::string>& matrixProperties);
    
    /**
     * @brief Simulate the Absorption, the RandomWalk and the Avalanches processes.
     * 
     * @param photons The photons that hit the SpadMatrix.
     * @param[out] avalanches The avalanche generated.
     */
    virtual void simulateAll(const Vector<Photon*>& photons, Vector<Avalanche*>& avalanches) = 0;
    
    /**
     * @brief Simulate the Absorption of photons into the Silicon SPAD.
     * 
     * Will only keep particles that have penetrate in the Spad surface and that were still inside after the absorption.
     * 
     * @param photons The photons that hit the SpadMatrix.
     * @param[out] absorbedParticle The particle that were absorbed in the Silicon.
     */
    virtual void simulateAbsorption(const Vector<Photon*>& photons, Vector<Particle*>& absorbedParticle) const = 0;
    
    /**
     * @brief Simulate the RandomWalk for the particle.
     * 
     * First the particles will be split into 3 groups depending on where they were absorbed (top, depletion zone and bottom).
     * 
     * For the ones in the top and bottom, make them move randomly to try to reach the depletion zone.
     * 
     * @warning The particles that didn't reach the depletion zone will be deleted.
     * 
     * @param[in,out] particles Take the absorbed particles and discard the ones that didn't reach the depletion zone
     */
    virtual void simulateRandomWalk(Vector<Particle*>& particles) const = 0;
    
    /**
     * @brief Simulate avalanche from Particles that reached the depletion zone
     * 
     * @warning Every particle that did not create an avalanche will be deleted. particles will be empty after this call.
     * 
     * @param particles The particles that reached the depletion zone
     * @param[out] avalanches The avalanche generated
     */
    virtual void simulateAvalanche(Vector<Particle*>& particles, Vector<Avalanche*>& avalanches) = 0;
    
    /**
     * @brief Reset the matrix's state.
     */
    virtual void resetMatrix();
};

#endif //I_SIMULATOR_H