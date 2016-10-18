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
 * File        : isilicon_factory.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef I_SILICON_FACTORY_H
#define I_SILICON_FACTORY_H

#include "iconfigurable_factory.hh"

class AbsorptionBehavior;
class ISilicon;

/**
 * @brief A derived IConfigurableFactory specialized for creating ISilicon.
 */
class ISiliconFactory : public IConfigurableFactory<ISilicon> {
private:
    ISiliconFactory(const ISiliconFactory&);
    ISiliconFactory& operator=(const ISiliconFactory&);
    
protected:
    /**
     * @brief Default constructor.
     */
    ISiliconFactory();
    
    /**
     * @brief Set the absorption behavior in the silicon.
     * 
     * @param silicon The silicon.
     * @param absorptionBehavior The absorption behavior.
     */
    virtual void setAbsorptionBehavior(ISilicon* silicon, AbsorptionBehavior* absorptionBehavior);
    
public:
    /**
     * @brief Destrictor.
     */
    virtual ~ISiliconFactory();
};

#endif //I_SILICON_FACTORY_H