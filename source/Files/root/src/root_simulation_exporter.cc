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
 * File        : root_simulation_exporter.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 16 16:01:05 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include <TTree.h>
#include <TFile.h>
#include <TROOT.h>

#include "avalanche.hh"
#include "log.hh"
#include "root_simulation_exporter.hh"
#include "root_include_lib.hh"

RootSimulationExporter::RootSimulationExporter(const std::string& filePath, const std::string& filter)
: SimulationExporter(filter)
, filePath(filePath)
{
    Clear();
    if (!vectorIncluded) {
        gROOT->ProcessLine("#include <vector>");
        vectorIncluded = true;
    }
    pGlobalTime = &globalTime;
    pTriggerType = &triggerType;
    pSpadX = &spadX;
    pSpadY = &spadY;
    
    file = new TFile(filePath.c_str(), "RECREATE", "", 9);
    tree = new TTree("tree", "name");
    tree->Branch("Event", &this->eventId, "Event/I");
    tree->Branch("PhotonCount", &this->photonCount, "PhotonCount/I");
    tree->Branch("SpadTriggeredCount", &this->spadTriggeredCount, "SpadTriggeredCount/I");
    tree->Branch("AvalancheCount", &this->avalancheCount, "AvalancheCount/I");
    tree->Branch("GlobalTime", "std::vector<float>", &pGlobalTime);
    tree->Branch("TriggerType", "std::vector<int>", &pTriggerType);
    tree->Branch("SpadX", "std::vector<float>", &pSpadX);
    tree->Branch("SpadY", "std::vector<float>", &pSpadY);
}

RootSimulationExporter::~RootSimulationExporter()
{
    tree->Write();
    file->Write();
    file->Close();
}

void RootSimulationExporter::Clear()
{
    eventId = photonCount = spadTriggeredCount = avalancheCount = 0;
    globalTime.clear();
    triggerType.clear();
    spadX.clear();
    spadY.clear();
}


void RootSimulationExporter::exportSimulation(const int& eventId, const int& photonCount, const Vector< Avalanche* >& avalanches)
{
    Vector<Avalanche*>::const_iterator it;
    Avalanche* avalanche;
    int exportedAvalancheCount = 0;
    int triggeredAvalanche = 0;
    for (it = avalanches.begin(); it != avalanches.end(); ++it) {
        avalanche = *it;
        if (avalancheIsExported(*avalanche)) {
            globalTime.push_back(avalanche->getGlobalTime());
            triggerType.push_back(avalanche->getTriggerType());
            spadX.push_back(avalanche->getSpadCoordinate().x);
            spadY.push_back(avalanche->getSpadCoordinate().y);
            ++exportedAvalancheCount;
        }
        if (!avalanche->isMasked()) {
            ++triggeredAvalanche;
        }
    }
    
    this->eventId = eventId;
    this->photonCount = photonCount;
    this->spadTriggeredCount = triggeredAvalanche;
    this->avalancheCount = exportedAvalancheCount;
    
    LOG_STREAM(2) << "Data Exported :" << std::endl; 
    LOG_STREAM(2) << "  Event ID :\t   " << eventId << std::endl;
    LOG_STREAM(2) << "  Photon Count :\t   " << photonCount << std::endl;
    LOG_STREAM(2) << "  SPAD Triggered Count : " << triggeredAvalanche << std::endl;
    LOG_STREAM(2) << "  Avalanche Count :\t   " << exportedAvalancheCount << std::endl;
    
    tree->Fill();
    Clear();
}
