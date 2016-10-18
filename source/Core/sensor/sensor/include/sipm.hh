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
 * File        : sipm.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Mar 15 10:13:19 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef SIPM_SENSOR_H
#define SIPM_SENSOR_H

#include "spad.hh"

class SipmConfiguration;
class SipmFactory;

#include "vector.hh"

/**
 * @brief Derived ISensor that represents a SiPM.
 */
class Sipm : public Spad {
private:
    friend class SipmFactory;
    
private:
    Sipm(const Sipm&);
    Sipm& operator=(const Sipm&);
    
    double totalQuenchTime;
    
    void calculateAnalogSignal(Vector<double>& time, 
                               Vector<double>& electricCurrent, 
                               double& spadTotalJitter, 
                               double& avalancheTotalJitter) const;

public:
    /**
     * @brief Constructor.
     */
    Sipm();
    
    /**
     * @brief Destructor.
     */
    virtual ~Sipm();
    
    /**
     * @brief Update the sensor states.
     * 
     * @param elapsed Time elapsed since last update.
     */
    virtual void update(const double& elapsed) override;
    
    /**
     * @brief Try triggering the sensor by hitting it with a particle.
     * 
     * @param particle The particle that hits the sensor.
     * @return Avalanche* The pointer will be set to 0 if no avalanche was created.
     */
    virtual Avalanche* trigger(Particle* particle) override;
    
protected:
    /**
     * @brief Set the state to quenching
     */
    void quench();
    
    /**
     * @brief Cast the sensor configuration into a SipmConfiguration.
     * 
     * @return SipmConfiguration*
     */
    SipmConfiguration* getSipmConfiguration() const;
};

#endif //SIPM_SENSOR_H