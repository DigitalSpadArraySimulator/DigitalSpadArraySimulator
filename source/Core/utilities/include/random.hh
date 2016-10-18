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
 * File        : random.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 2 15:19:04 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef RANDOM_UTILITIES_H
#define RANDOM_UTILITIES_H

#include <random>

/**
 * @brief This class wraps every usage of random generation.
 */
class RandomGenerator {
private:
    RandomGenerator();
    RandomGenerator(const RandomGenerator&);
    RandomGenerator& operator=(const RandomGenerator&);
    ~RandomGenerator();
    
    static std::default_random_engine generator;
    
public:
    
    /**
     * @brief Allow the user to set the seed to a specified number.
     * @param seed
     * @return void
     */
    static void seed(const int& seed);
    
    /**
     * @brief Generate a random number between 0 and 1.
     * @return double
     */
    static double rand();
    
    /**
     * @brief Return a random boolean according to Bernoulli distribution.
     * 
     * \f[P(b|p)=\begin{cases}
     * p &, b = true \\
     * 1 - p &, b = false \\
     * \end{cases}\f]
     * @param p The probability to get true.
     * @warning p \f$p\f$ value must be between 0 and 1.
     * @return bool \f$b\f$.
     * @see http://www.cplusplus.com/reference/random/bernoulli_distribution/
     */
    static bool bernoulli(const double& p);
    
    /**
     * @brief Return a random double according to an exponential distribution..
     * 
     * \f[p(x|\lambda)=\lambda*e^{-\lambda*x}\f]
     * @param lambda \f$\lambda\f$ The exponential distribution rate.
     * @warning lambda is the rate, not the scale (beta - \f$\beta\f$ ). \f$\lambda=1/\beta\f$
     * @return double
     * @see http://www.cplusplus.com/reference/random/exponential_distribution/
     */
    static double exponential(const double& lambda);
    
    /**
     * @brief Return a random double according to a chi squared distribution.
     * 
     * \f[p(x|n)=\frac{1}{\Gamma(\frac{n}{2})*2^{\frac{n}{2}}}*x^{\frac{n}{2}-1}*e^{-\frac{x}{2}}, x\geq0\f]
     * @param n The chi squared degree.
     * @return double
     * @see http://www.cplusplus.com/reference/random/chi_squared_distribution/
     */
    static double chiSquared(const double& n);
    
    /**
     * @brief Return a random double according to a normal distribution.
     * 
     * \f[p(x|\mu,\sigma)=\frac{1}{\sigma\sqrt{2\pi}}*e^{-\frac{(x-\mu)^2}{2\sigma^2}}\f]
     * @param mean \f$\mu\f$ Mean of the distribution.
     * @param stddev \f$\sigma\f$ Standard deviation.
     * @return double
     * @see http://www.cplusplus.com/reference/random/normal_distribution/
     */
    static double normal(const double& mean = 0.0, const double& stddev = 1.0);
};

#endif //RANDOM_UTILITIES_H