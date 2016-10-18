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
 * File        : dark_count_generator.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 9 15:09:28 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef DARK_COUNT_GENERATOR_GENERATOR_H
#define DARK_COUNT_GENERATOR_GENERATOR_H

#include "vector.hh"
#include "igenerator.hh"

class ISensorMatrix;
class Particle;
class DarkCount;

/**
 * @brief Generate dark counts on a sensor matrix.
 */
class DarkCountGenerator : public IGenerator<DarkCount> {
private:
    DarkCountGenerator();
    DarkCountGenerator(const DarkCountGenerator&);
    DarkCountGenerator& operator=(const DarkCountGenerator&);
    
public:
    /**
     * @brief Constructor.
     * 
     * @param simulator A reference to the simulator using this generator.
     */
    DarkCountGenerator(ISimulator const * simulator);
    
    /**
     * @brief Destructor.
     */
    virtual ~DarkCountGenerator();
    
    /**
     * @brief Generate dark counts for a certain amount of time.
     * 
     * @param lastParticle The last particle that will hit the matrix.
     * @param[out] out The created dark counts.
     */
    virtual void generate(Particle* const lastParticle, Vector<Particle*>& out) override;
};

#endif //DARK_COUNT_GENERATOR_GENERATOR_H