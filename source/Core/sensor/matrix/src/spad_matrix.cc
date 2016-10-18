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
 * File        : spad_matrix.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include <stdexcept>
#include <math.h>

#include "constants.hh"
#include "coordinate.hh"
#include "isensor.hh"
#include "particle.hh"
#include "photon.hh"
#include "polygon.hh"
#include "position.hh"
#include "random.hh"
#include "silicon.hh"
#include "spad.hh"
#include "spad_configuration.hh"
#include "spad_configuration_factory.hh"
#include "spad_factory.hh"
#include "spad_matrix.hh"
#include "var_type.hh"
#include <isensor_configuration.hh>
#include <isimulator.hh>

SpadMatrix::SpadMatrix() 
: ISensorMatrix()
{}

SpadMatrix::~SpadMatrix()
{}

void SpadMatrix::randomWalk(Vector<Particle*>& particles, const bool& fromTop, Vector<Particle*>& output) const
{
    Vector<Particle*>::iterator it;
    double k = PhysicsConstants::get(PhysicsConstants::BOLTZMANN_CONSTANT_J);
    double q = PhysicsConstants::get(PhysicsConstants::ELECTRON_CHARGE);
    double m0 = PhysicsConstants::get(PhysicsConstants::ELECTRON_REST_MASS);
    double T = sensorConfiguration->getPropertyAs<double>(SpadConfiguration::TEMPERATURE);
    double mc, mu, vth, tau, a;
    double meanLifetime = 100e-6;
    ISensor* sensor;
    Particle* particle;
    if (fromTop) {
        mc = simulator->getSilicon()->getPropertyAs<double>(ISilicon::MASS_CONDUCTIVITY_ELECTRON);
        mu = simulator->getSilicon()->getPropertyAs<double>(ISilicon::P_ZONE_ELECTRON_MOBILITY);
    } else {
        mc = simulator->getSilicon()->getPropertyAs<double>(ISilicon::MASS_CONDUCTIVITY_HOLE);
        mu = simulator->getSilicon()->getPropertyAs<double>(ISilicon::N_ZONE_HOLE_MOBILITY);
    }
    vth = 1.0e6 * sqrt(3.0 * k * T / (mc * m0));
    tau = mu * mc * m0 / q;
    a = vth / 2 * sqrt(M_PI_2);
    for (it = particles.begin(); it != particles.end(); ) {
        particle = *it;
        sensor = (*this)[particle->getSensorCoordinate()];
        if (sensor->randomWalk(*particle, meanLifetime, fromTop, tau, a)) {
            output.push_back(particle);
            it = particles.erase(it);
        } else {
            it++;
        }
    }
}

void SpadMatrix::sortByDepth(Vector<Particle*>& all, Vector<Particle*>& top, Vector<Particle*>& dep, Vector<Particle*>& bottom)
{
    double depStart = -sensorConfiguration->getPropertyAs<double>(SpadConfiguration::SPAD_TOP_DEPTH);
    double depEnd = -sensorConfiguration->getPropertyAs<double>(SpadConfiguration::SPAD_DEP_DEPTH);
    Vector<Particle*>::iterator it;
    Particle* particle;
    double z;
    for (it = all.begin(); it != all.end(); ) {
        particle = *it;
        z = particle->getPosition().z;
        if (z > depStart) {
            top.push_back(particle);
        } else if (depStart >= z && z >= depEnd) {
            dep.push_back(particle);
        } else {
            bottom.push_back(particle);
        }
        it = all.erase(it);
    }
}
