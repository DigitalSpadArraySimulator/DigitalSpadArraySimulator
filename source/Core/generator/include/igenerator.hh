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
 * File        : igenerator.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Apr 7 14:43:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef I_GENERATOR_H
#define I_GENERATOR_H

template <typename T> class Vector;

class Particle;
class ISimulator;

/**
 * @brief Abstract particle generator class.
 */
template <typename T>
class IGenerator {
private:
    IGenerator();
    IGenerator(const IGenerator&);
    IGenerator& operator=(const IGenerator&);
    
protected:
    /**
     * @brief Constructor.
     * 
     * @param simulator A reference to the simulator using this generator.
     */
    IGenerator(ISimulator const  * simulator);
    
    /**
     * @brief A reference to the simulator using this generator.
     */
    ISimulator const * simulator;
    
public:
    /**
     * @brief Destructor.
     * 
     * @warning The simulator will not be deleted.
     */
    virtual ~IGenerator();
    
    /**
     * @brief Generate particles based on a particle.
     * 
     * @param source The particle used to generate other particles.
     * @param[out] out The particle generated.
     */
    virtual void generate(Particle* const source, Vector<Particle*>& out) = 0;
};

#include "igenerator.hpp"

#endif //I_GENERATOR_H