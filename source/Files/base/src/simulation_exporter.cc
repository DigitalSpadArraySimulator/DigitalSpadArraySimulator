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
 * File        : simulation_exporter.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Wed Mar 16 16:01:05 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "simulation_exporter.hh"
#include "avalanche.hh"
#include "particle.hh"

SimulationExporter::SimulationExporter(const std::string& filter)
{
    analyseFilter(filter);
}


void SimulationExporter::analyseFilter(const std::string& filter)
{
    maskedFlag          = filter.find('M') != -1;
    bool defaultFlag    = filter.find('S') == -1;
    crosstalkFlag       = (filter.find('C') != -1 ? true : defaultFlag);
    afterpulseFlag      = (filter.find('A') != -1 ? true : defaultFlag);
    darkCountFlag       = (filter.find('D') != -1 ? true : defaultFlag);
    cerenkovFlag        = (filter.find('K') != -1 ? true : defaultFlag);
    promptFlag          = (filter.find('F') != -1 ? true : defaultFlag);
    photonFlag          = (filter.find('P') != -1 ? true : defaultFlag);
}

bool SimulationExporter::avalancheIsExported(const Avalanche& avalanche)
{
    bool retval = false;
    if (maskedFlag || !avalanche.isMasked()) {
        switch (avalanche.getTriggerType()) {
            case Particle::AFTERPULSING:
                retval = afterpulseFlag;
                break;
            case Particle::CERENKOV_PHOTON:
                retval = cerenkovFlag;
                break;
            case Particle::Particle::OPTICAL_CROSSTALK:
                retval = crosstalkFlag;
                break;
            case Particle::PHOTON:
                retval = photonFlag;
                break;
            case Particle::PROMPT_PHOTON:
                retval = promptFlag;
                break;
            case Particle::THERMAL_NOISE:
                retval = darkCountFlag;
                break;
        }
    }
    return retval;
}
