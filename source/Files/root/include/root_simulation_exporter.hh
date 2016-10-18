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
 * File        : root_simulation_exporter.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 16 16:01:05 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef ROOT_EVENT_EXPORTER_ROOT_H
#define ROOT_EVENT_EXPORTER_ROOT_H

#include "simulation_exporter.hh"
#include <vector>

class TFile;
class TTree;

/**
 * @brief Derived SimulationExporter that write Root file (.root).
 */
class RootSimulationExporter : public SimulationExporter {
private:
    RootSimulationExporter();
    RootSimulationExporter(const RootSimulationExporter&);
    RootSimulationExporter& operator=(const RootSimulationExporter&);
    
    std::string filePath;
    
    TFile* file;
    TTree* tree;
    
    std::vector<float> globalTime, spadX, spadY, *pGlobalTime, *pSpadX, *pSpadY;
    std::vector<int> triggerType, *pTriggerType;
    
    int eventId, photonCount, spadTriggeredCount, avalancheCount;
    
    void Clear();
    
public:
    /**
     * @brief Constructor.
     * 
     * @param filePath The path to the file to create. (ex: /home/bob/Simulation.root)
     * @param filter The filter that indicate which avalanches are exported.
     */
    RootSimulationExporter(const std::string& filePath, const std::string& filter);
    
    /**
     * @brief Destructor.
     */
    virtual ~RootSimulationExporter();
    
    virtual void exportSimulation(const int& eventId, 
                                  const int& photonCount,
                                  const Vector<Avalanche*>& avalanches) override;
};

#endif //ROOT_EVENT_EXPORTER_ROOT_H