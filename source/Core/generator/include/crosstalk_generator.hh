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
 * File        : crosstalk_generator.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 10 07:39:28 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef CROSSTALK_GENERATOR_GENERATOR_H
#define CROSSTALK_GENERATOR_GENERATOR_H

#include "igenerator.hh"

#include "coordinate.hh"
#include "map.hh"
#include "vector.hh"

class Crosstalk;
class Particle;
class ISensorMatrix;

/**
 * @brief Generate crosstalk on a sensor matrix
 */
class CrosstalkGenerator : public IGenerator<Crosstalk>{
private:
    CrosstalkGenerator();
    CrosstalkGenerator(const CrosstalkGenerator&);
    CrosstalkGenerator& operator=(const CrosstalkGenerator&);
    
    Crosstalk* createCrosstalk(Particle* parent, const Coordinate2D& spadCoord);

protected:
    /**
     * @brief Generate a map of distance and associated probability.
     * 
     * The distance is calculated like this: \f$|x-x_{source}| + |y-y_{source}|\f$
     * 
     * @param[out] probs The probabilities based on the distance.
     * 
     * \f[Distance :
     *    \begin{array}{ccccc}
     *     4 & 3 & 2 & 3 & 4 \\
     *     3 & 2 & 1 & 2 & 3 \\
     *     2 & 1 & 0 & 1 & 2 \\
     *     3 & 2 & 1 & 2 & 3 \\
     *     4 & 3 & 2 & 3 & 4 \end{array}\f]
     */
    virtual void initProbs(Map<int, double>& probs) const;
    
    /**
     * @brief Try to generate a crosstalk on every sensor included by the optical crosstalk range.
     * 
     * @param source The particle that caused an Avalanch.
     * @param[out] out The created crosstalks.
     * @param probs The probabilities based on the distance.
     * @param opticalCrosstalkRange The range of this loop. 
     * 
     * \f[Range :
     *    \begin{array}{ccccc}
     *     2 & 2 & 2 & 2 & 2 \\
     *     2 & 1 & 1 & 1 & 2 \\
     *     2 & 1 & 0 & 1 & 2 \\
     *     2 & 1 & 1 & 1 & 2 \\
     *     2 & 2 & 2 & 2 & 2 \end{array}\f]
     */
    virtual void generateCrosstalkLoop(Particle* const source,
                                       Vector<Particle*>& out,
                                       const Map<int, double>& probs,
                                       const int& opticalCrosstalkRange);
    
public:
    /**
     * @brief Constructor.
     * 
     * @param simulator A reference to the simulator using this generator.
     */
    CrosstalkGenerator(ISimulator const* simulator);
    
    /**
     * @brief Destructor.
     */
    virtual ~CrosstalkGenerator();
    
    /**
     * @brief Generate 0 to 8 crosstalks depending on the random.
     * 
     * @warning This function will access sensor properties defined in SpadConfiguration.
     * SpadConfiguration::SPAD_TOP_DEPTH and SpadConfiguration::CROSSTALK_PROB needs to be in the sensors configuration.
     * 
     * @param source The particle that caused an Avalanch.
     * @param[out] out The created crosstalks.
     */
    virtual void generate(Particle* const source, Vector<Particle*>& out) override;
};

#endif //CROSSTALK_GENERATOR_GENERATOR_H