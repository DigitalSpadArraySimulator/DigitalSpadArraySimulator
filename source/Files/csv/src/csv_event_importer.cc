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
 * File        : csv_event_importer.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Apr 13 15:19:01 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "csv_event_importer.hh"

#include <iostream>
#include <fstream>
#include <stdio.h>

#include "constants.hh"
#include "isensor_matrix.hh"
#include "photon.hh"
#include "vector.hh"

CsvEventImporter::CsvEventImporter(const std::string& filepath)
: EventImporter()
, filepath(filepath)
{}

CsvEventImporter::~CsvEventImporter()
{}

Particle::ParticleType CsvEventImporter::interpreteType(const int& type)
{
    Particle::ParticleType result;
    switch(type) {
        case 1:
            result = Particle::CERENKOV_PHOTON;
            break;
        case 2:
            result = Particle::PROMPT_PHOTON;
            break;
        default:
            result = Particle::PHOTON;
    }
    return result;
}

void CsvEventImporter::importSingleEvent(const int& eventId, 
                                         const ISensorMatrix& matrix,
                                         const double& timeDelay, 
                                         Vector< Photon* >& photons)
{
    photons.clearAndDelete();
    std::ifstream file (filepath);
    
    if (!file.is_open()) {
        throw std::invalid_argument("Could not open the specified CSV file.");
    }
    
    Position2D matrixCenter = matrix.getCenter();
    Position2D crystalOffset = matrix.getCrystalOffset();
    int count, type;
    double globalTime, energie, wavelength;
    double hc = PhysicsConstants::get(PhysicsConstants::PlANCK_SPEED_LIGHT);
    Position2D penetrationPoint;
    Position3D postMomentum;
    Particle::ParticleType photonType;
    
    std::string line;
    while (getline(file, line)) {
        count = std::sscanf(line.c_str(), 
                                "%lf;%lf;%lf;%lf;%lf;%lf;%d;%lf", 
                                &globalTime, 
                                &penetrationPoint.x, 
                                &penetrationPoint.y,
                                &postMomentum.x,
                                &postMomentum.y,
                                &postMomentum.z,
                                &type,
                                &energie);
        if (count != 8) {
            throw std::logic_error("The csv format was not respected");
        }
        
        globalTime += timeDelay;
        penetrationPoint.x = penetrationPoint.x * 1000 + matrixCenter.x + crystalOffset.x;
        penetrationPoint.y = penetrationPoint.y * 1000 + matrixCenter.y + crystalOffset.y;
        photonType = interpreteType(type);
        wavelength = hc * 1000 / energie;
        
        photons.push_back(new Photon(globalTime, 
                                     penetrationPoint,
                                     postMomentum,
                                     photonType,
                                     wavelength));
    }
}

