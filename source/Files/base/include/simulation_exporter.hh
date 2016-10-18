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
 * File        : simulation_exporter.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 16 16:01:05 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef SIMULATION_EXPORTER_BASE_H
#define SIMULATION_EXPORTER_BASE_H

#include <string>

#include "vector.hh"
class Avalanche;

/**
 * @class SimulationExporter
 * @brief Export the result of the simulation.
 * @warning This class is not meant to export data that will be import by EventImporter.
 */
class SimulationExporter {
private:
    SimulationExporter();
    SimulationExporter(const SimulationExporter&);
    SimulationExporter& operator=(const SimulationExporter&);
    
protected:
    /**
     * @brief If true, the Masked Avalanche will be exported.
     * @see EventExporter::analyseFilter
     */
    bool maskedFlag; 
    
    /**
     * @brief If true, the Avalanche caused by an Afterpulse will be exported.
     * @see EventExporter::analyseFilter
     */
    bool afterpulseFlag;
    
    /**
     * @brief If true, the Avalanche caused by a Cerenkov Photon will be exported.
     * @see EventExporter::analyseFilter
     */
    bool cerenkovFlag;
    
    /**
     * @brief If true, the Avalanche caused by a Crosstalk will be exported.
     * @see EventExporter::analyseFilter
     */
    bool crosstalkFlag;
    
    /**
     * @brief If true, the Avalanche caused by a DarkCount will be exported.
     * @see EventExporter::analyseFilter
     */
    bool darkCountFlag;
    
    /**
     * @brief If true, the Avalanche caused by a Standard Photon will be exported.
     * @see EventExporter::analyseFilter
     */
    bool photonFlag;
    
    /**
     * @brief If true, the Avalanche caused by a Prompt Photon will be exported.
     * @see EventExporter::analyseFilter
     */
    bool promptFlag;
    
    /**
     * @brief Create an event exporter with a specific filter.
     * 
     * @param filter The filter that decides which avalanches are exported.
     * @see EventExporter::analyseFilter
     */
    SimulationExporter(const std::string& filter);
    
    /**
     * @brief Analyse the given filter and set the flags.
     * 
     * @param filter The following value can be used:
     * 
     *     M : If present, include masked avalanche (not triggered)
     * 
     *     S : If present, only specified trigger type* are included
     * 
     *         If not present, include every trigger type
     * 
     *     A : If present, include Afterpulses trigger type
     * 
     *     C : If present, include Crosstalks trigger type
     * 
     *     D : If present, include DarkCounts trigger type
     * 
     *     F : If present, include PromptPhoton (Fast) trigger type
     * 
     *     K : If present, include CerenkovPhoton trigger type
     * 
     *     P : If present, include Photon trigger type   
     * 
     *     example : "MSFKP" will output every avalanche, even masked one, that were caused by any type of photon.
     */
    virtual void analyseFilter(const std::string& filter);
    /**
     * @brief Check with the flags if the avalanche is exported or not.
     * 
     * @param avalanche
     * @return bool
     */
    virtual bool avalancheIsExported(const Avalanche& avalanche);
    
public:
    /**
     * @brief Destructor
     */
    virtual ~SimulationExporter() {}
    
    /**
     * @brief Export a single event with basic informations.
     * 
     * @param eventId The id of the event
     * @param photonCount The number of Photon before the absorption.
     * @param avalanches All the Avalache that occured during this event.
     */
    virtual void exportSimulation(const int& eventId, 
                                  const int& photonCount,
                                  const Vector<Avalanche*>& avalanches) = 0;
};

#endif //SIMULATION_EXPORTER_BASE_H