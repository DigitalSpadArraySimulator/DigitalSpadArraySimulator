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
 * File        : csv_event_importer.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Apr 13 15:19:01 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef CSV_EVENT_IMPORTER_H
#define CSV_EVENT_IMPORTER_H

#include <string>

#include "event_importer.hh"
#include "particle.hh"

/**
 * @brief Derived EventImporter that imports photons from a file.
 * 
 * @warning This importer will always import the same event.
 */
class CsvEventImporter : public EventImporter {
private:
    CsvEventImporter();
    CsvEventImporter(const EventImporter&);
    CsvEventImporter& operator=(const EventImporter&);
    
    std::string filepath;
    
    Particle::ParticleType interpreteType(const int& type);
    
public:
    /**
     * @brief Constructor.
     * 
     * @param filepath The CSV file path to read.
     */
    CsvEventImporter(const std::string& filepath);
    
    /**
     * @brief Destructor.
     * 
     */
    virtual ~CsvEventImporter();
    
    virtual void importSingleEvent(const int& eventId, 
                                   const ISensorMatrix& matrix, 
                                   const double& timeDelay, 
                                   Vector<Photon*>& photons) override;
};

#endif //CSV_EVENT_IMPORTER_H