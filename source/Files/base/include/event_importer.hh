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
 * File        : event_importer.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 16 16:01:05 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef EVENT_IMPORTER_BASE_H
#define EVENT_IMPORTER_BASE_H

class Photon;
class ISensorMatrix;
template<typename T> class Vector;

struct Position2D;

/**
 * @brief Abstract class to import an event's photons.
 * @warning This class is not meant to import data exported by SimulationExporter.
 */
class EventImporter {
private:
    EventImporter(const EventImporter&);
    EventImporter& operator=(const EventImporter&);
protected:
    /**
     * @brief Constructor.
     */
    EventImporter();
    
public:
    /**
     * @brief Destructor.
     */
    virtual ~EventImporter() {}
    
    /**
    * @brief Import a single event.
    * 
    * @param eventId The event ID.
    * @param matrix The matrix with the offset properties.
    * @param timeDelay Time offset used to delay the event.
    * @param [out] photons The photon imported.
    */
    virtual void importSingleEvent(const int& eventId, 
                                   const ISensorMatrix& matrix, 
                                   const double& timeDelay,
                                   Vector<Photon*>& photons) = 0;
};

#endif //EVENT_IMPORTER_BASE_H