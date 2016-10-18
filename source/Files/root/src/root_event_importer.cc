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
 * File        : root_event_importer.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 10:16:29 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "root_event_importer.hh"

#include <string>
#include <sstream>

#include <TTree.h>
#include <TFile.h>
#include <TROOT.h>

#include "isensor_matrix.hh"
#include "log.hh"
#include "position.hh"
#include "photon.hh"
#include "vector.hh"
#include "constants.hh"
#include "root_include_lib.hh"
#include "spad_matrix.hh"
#include "var_type.hh"

RootEventImporter::RootEventImporter(const std::string& filename)
: EventImporter()
, pGlobalTime(0)
, pPositionX(0)
, pPositionY(0)
, pPostMomentumX(0)
, pPostMomentumY(0)
, pPostMomentumZ(0)
, pPhotonType(0)
, pPhotonEnergy(0)
{
    if (!vectorIncluded) {
        gROOT->ProcessLine("#include <vector>");
        vectorIncluded = true;
    }
    file = new TFile(filename.c_str(), "READ");
    tree = (TTree*) file->Get("tree");
    tree->SetBranchAddress("GlobalTime", &pGlobalTime);
    tree->SetBranchAddress("PositionX", &pPositionX);
    tree->SetBranchAddress("PositionY", &pPositionY);
    tree->SetBranchAddress("PostMomentumX", &pPostMomentumX);
    tree->SetBranchAddress("PostMomentumY", &pPostMomentumY);
    tree->SetBranchAddress("PostMomentumZ", &pPostMomentumZ);
    tree->SetBranchAddress("PhotonType", &pPhotonType);
    tree->SetBranchAddress("PhotonEnergy", &pPhotonEnergy);
}

RootEventImporter::~RootEventImporter()
{
    file->Close();
    delete file;
    file = 0;
    tree = 0;
    pGlobalTime = pPositionX = pPositionY = pPostMomentumX = pPostMomentumY = pPostMomentumY = pPostMomentumZ = pPhotonEnergy = 0;
    pPhotonType = 0;
}

Particle::ParticleType RootEventImporter::interpreteType(const int& type)
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

void RootEventImporter::importSingleEvent(const int& eventId, 
                                      const ISensorMatrix& matrix,
                                      const double& timeDelay,
                                      Vector<Photon*>& photons)
{
    photons.clearAndDelete();
    tree->GetEntry(eventId);
    
    Position2D matrixCenter = matrix.getCenter();
    Position2D crystalOffset = matrix.getCrystalOffset();
    double globalTime, wavelength;
    Position2D penetrationPoint;
    Position3D postMomentum;
    Particle::ParticleType photonType;
    double hc = PhysicsConstants::get(PhysicsConstants::PlANCK_SPEED_LIGHT);
    
    for (int i = 0; i < pGlobalTime->size(); ++i) {
        globalTime = (*pGlobalTime)[i] + timeDelay;
        penetrationPoint.x = (*pPositionX)[i] * 1000 + matrixCenter.x + crystalOffset.x;
        penetrationPoint.y = (*pPositionY)[i] * 1000 + matrixCenter.y + crystalOffset.y;
        postMomentum.x = (*pPostMomentumX)[i];
        postMomentum.y = (*pPostMomentumY)[i];
        postMomentum.z = (*pPostMomentumZ)[i];
        photonType = interpreteType((*pPhotonType)[i]);
        wavelength = hc * 1000 / (*pPhotonEnergy)[i];
        photons.push_back(new Photon(globalTime, 
                                     penetrationPoint,
                                     postMomentum,
                                     photonType,
                                     wavelength));
    }
#ifdef VERBOSE
    std::stringstream ss;
    ss << "Event #" << eventId << " imported"; 
    LOG(ss.str(), 2);
#endif
}
