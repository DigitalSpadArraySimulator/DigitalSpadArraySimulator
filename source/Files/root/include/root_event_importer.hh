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
 * File        : root_event_importer.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 10:16:29 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#ifndef ROOT_EVENT_IMPORTER_IMPORTER_H
#define ROOT_EVENT_IMPORTER_IMPORTER_H

#include <string>
#include <vector>

#include "event_importer.hh"
#include "particle.hh"

struct Position2D;
class Photon;
class SpadMatrix;
class TFile;
class TTree;
template<typename T> class Vector;

/**
 * @brief Class used to import an event from a root file.
 */
class RootEventImporter : public EventImporter {
private:
    RootEventImporter();
    RootEventImporter(const RootEventImporter&);
    RootEventImporter& operator=(const RootEventImporter&);
    
    TFile* file;
    TTree* tree;
    
    std::vector<float>* pGlobalTime;
    std::vector<float>* pPositionX;
    std::vector<float>* pPositionY;
    std::vector<float>* pPostMomentumX;
    std::vector<float>* pPostMomentumY;
    std::vector<float>* pPostMomentumZ;
    std::vector<float>* pPhotonEnergy;
    std::vector<int>*   pPhotonType;
    
    Particle::ParticleType interpreteType(const int& type);
    
public:
    /**
     * @brief Constructor.
     * 
     * @param filename The full path to the file to import.
     */
    RootEventImporter(const std::string& filename);
    
    /**
     * @brief Destructor.
     */
    virtual ~RootEventImporter();
    
    virtual void importSingleEvent(const int& eventId, 
                                   const ISensorMatrix& matrix,
                                   const double& timeDelay,
                                   Vector<Photon*>& photons) override;
};

#endif //ROOT_EVENT_IMPORTER_IMPORTER_H