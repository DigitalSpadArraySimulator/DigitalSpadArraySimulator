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
 * File        : laser_event_importer.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Apr 13 14:09:34 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef LASER_EVENT_IMPORTER_H
#define LASER_EVENT_IMPORTER_H

#include "event_importer.hh"

/**
 * @brief Derived EventImporter that generates photons randomly positionned on the matrix.
 */
class LaserEventImporter : public EventImporter {
private:
    LaserEventImporter();
    LaserEventImporter(const LaserEventImporter&);
    LaserEventImporter& operator=(const LaserEventImporter&);
    
    int photonsPerEvent;
    double wavelength;

public:
    /**
     * @brief Constructor.
     * 
     * @param photonsPerEvent The number of photons to generate for each event.
     * @param wavelength The wavelength of the photons.
     */
    LaserEventImporter(const int& photonsPerEvent, const double& wavelength);
    /**
     * @brief Destructor.
     */
    virtual ~LaserEventImporter();
    
    virtual void importSingleEvent(const int& eventId, 
                                   const ISensorMatrix& matrix, 
                                   const double& timeDelay, 
                                   Vector< Photon* >& photons) override;
};

#endif //LASER_EVENT_IMPORTER_H