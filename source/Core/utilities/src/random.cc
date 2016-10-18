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
 * File        : random.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 2 15:19:04 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include <stdexcept>
#include "random.hh"

std::default_random_engine RandomGenerator::generator;

void RandomGenerator::seed(const int& seed)
{
    generator.seed(seed);
}

double RandomGenerator::rand()
{
    return ((double) generator() / RAND_MAX);
}

bool RandomGenerator::bernoulli(const double& p)
{
    std::bernoulli_distribution distribution(p);
    return distribution(generator);
}

double RandomGenerator::exponential(const double& lambda)
{
    std::exponential_distribution<double> distribution(lambda);
    return distribution(generator);
}

double RandomGenerator::chiSquared(const double& n)
{
    std::chi_squared_distribution<double> distribution(n);
    return distribution(generator);
}

double RandomGenerator::normal(const double& mean, const double& stddev)
{
    std::normal_distribution<double> distribution(mean, stddev);
    return distribution(generator);
}
