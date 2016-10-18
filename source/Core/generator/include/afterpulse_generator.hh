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
 * File        : afterpulse_generator.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 10 08:39:50 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef AFTERPULSE_GENERATOR_GENERATOR_H
#define AFTERPULSE_GENERATOR_GENERATOR_H

#include "igenerator.hh"

class Afterpulse;
class Particle;
class ISensorMatrix;

/**
 * @brief Generate afterpulses for a simulation.
 */
class AfterpulseGenerator : public IGenerator<Afterpulse>{
private:
    AfterpulseGenerator();
    AfterpulseGenerator(const AfterpulseGenerator&);
    AfterpulseGenerator& operator=(const AfterpulseGenerator&);
    
protected:
    /**
     * @brief Create an afterpulse particle based on a parend particle.
     * 
     * @param parent The parent particle.
     * @return Afterpulse*
     */
    Afterpulse* createAfterpulse(Particle* parent);
    
public:
    /**
     * @brief Constructor.
     * 
     * @param simulator A reference to the simulator using this generator.
     */
    AfterpulseGenerator(ISimulator* simulator);
    
    /**
     * @brief Destructor
     */
    ~AfterpulseGenerator();
    
    /**
     * @brief Generate 0 or 1 afterpulse depending on the random.
     * 
     * @param source The particle that triggered an avalanche and may cause an afterpulse.
     * @param[out] out Will be empty or will contain a single afterpulse.
     */
    virtual void generate(Particle* const source, Vector<Particle*>& out) override;
};

#endif //AFTERPULSE_GENERATOR_GENERATOR_H