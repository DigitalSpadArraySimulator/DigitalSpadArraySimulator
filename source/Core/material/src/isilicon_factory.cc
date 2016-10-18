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
 * File        : isilicon_factory.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "isilicon_factory.hh"

#include <stdexcept>

#include "isilicon.hh"
#include "absorption_behavior.hh"

ISiliconFactory::ISiliconFactory()
: IConfigurableFactory<ISilicon>() 
{}

ISiliconFactory::~ISiliconFactory()
{}

void ISiliconFactory::setAbsorptionBehavior(ISilicon* silicon, AbsorptionBehavior* absorptionBehavior)
{
    if (!absorptionBehavior){
        throw std::logic_error("The given AbsorptionBehavior is not a valid one.");
    }
    
    if (silicon->absorptionBehavior != absorptionBehavior){
        if (silicon->absorptionBehavior) {
            delete silicon->absorptionBehavior;
        }
        
        silicon->absorptionBehavior = absorptionBehavior;
    }
}
