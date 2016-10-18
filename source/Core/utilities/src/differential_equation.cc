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
 * File        : differential_equation.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Fri Mar 4 16:57:33 2016 -0500 by valentin
 * 
 * FILE_INFO_END */


#include "differential_equation.hh"
#include <math.h>
#include <algorithm>

void calculateProbabilitiesFromElectricField(const Vector<double>& electricField,
                                       const Vector<double>& z,
                                       const double& dz,
                                       Vector<double>& probElectron,
                                       Vector<double>& probHole){
    Vector<double>::const_iterator it;
    probElectron.clear();
    probElectron.resize(z.size(), 0);
    probHole.clear();
    probHole.resize(z.size(), 0);
    
    double Eie = 3.6;  // eV
    double Fie = 1.954e6; // eV/cm
    double Fre = 1.069e5; // eV/cm
    double Fkte = 1.357e4; // eV/cm
    
    double Eih = 5; // eV
    double Fih = 3.091e6; // eV/cm
    double Frh = 1.11e5; // eV/cm
    double Fkth = 1.545e4; // eV/cm
    
    Vector<double> alphae, alphah;
    
    for (it = electricField.begin(); it != electricField.end(); ++it){
        double e = ((*it)/ Eie) * exp(-Fie / ((*it) * (1 + (*it) / Fre) + Fkte));
        double h = ((*it) / Eih) * exp(-Fih / ((*it) * (1 + (*it) / Frh) + Fkth));
        
        alphae.push_back(e);
        alphah.push_back(h);
    }
    
    double HighValue = 1;
    double LowValue = 0;
    double CurrentValue = 0.5;
    bool flag = true;
    double kPe1, kPh1, kPe2, kPh2;
    double kPe3, kPh3, kPe4, kPh4;
    
    while (flag) {
        probElectron[0] = CurrentValue;
        probHole[0] = 0;
        for (int i = 0; i < z.size() - 1; i++) {
            kPe1 = -(1-probElectron[i])*alphae[i]*(probElectron[i]+probHole[i]-probElectron[i]*probHole[i]);
            kPh1 = (1-probHole[i])*alphah[i]*(probElectron[i]+probHole[i]-probElectron[i]*probHole[i]);
            kPe2 = -(1-(probElectron[i]+dz*kPe1/2))*((alphae[i]+alphae[i+1])/2)*((probElectron[i]+dz*kPe1/2)+(probHole[i]+dz*kPh1/2)-(probElectron[i]+dz*kPe1/2)*(probHole[i]+dz*kPh1/2));
            kPh2 = (1-(probHole[i]+dz*kPh1/2))*((alphah[i]+alphah[i+1])/2)*((probElectron[i]+dz*kPe1/2)+(probHole[i]+dz*kPh1/2)-(probElectron[i]+dz*kPe1/2)*(probHole[i]+dz*kPh1/2));
            kPe3 = -(1-(probElectron[i]+dz*kPe2/2))*((alphae[i]+alphae[i+1])/2)*((probElectron[i]+dz*kPe2/2)+(probHole[i]+dz*kPh2/2)-(probElectron[i]+dz*kPe2/2)*(probHole[i]+dz*kPh2/2));
            kPh3 = (1-(probHole[i]+dz*kPh2/2))*((alphah[i]+alphah[i+1])/2)*((probElectron[i]+dz*kPe2/2)+(probHole[i]+dz*kPh2/2)-(probElectron[i]+dz*kPe2/2)*(probHole[i]+dz*kPh2/2));
            kPe4 = -(1-(probElectron[i]+dz*kPe3/2))*alphae[i+1]*((probElectron[i]+dz*kPe3)+(probHole[i]+dz*kPh3)-(probElectron[i]+dz*kPe3)*(probHole[i]+dz*kPh3));
            kPh4 = (1-(probHole[i]+dz*kPh3))*alphah[i+1]*((probElectron[i]+dz*kPe3)+(probHole[i]+dz*kPh3)-(probElectron[i]+dz*kPe3)*(probHole[i]+dz*kPh3));
            
            probElectron[i+1] = probElectron[i] + dz/6*(kPe1+2*kPe2+2*kPe3+kPe4);
            probHole[i+1] = probHole[i] + dz/6*(kPh1+2*kPh2+2*kPh3+kPh4);
        }
        if (probElectron.back() > 1e-9){
            HighValue = CurrentValue;
            CurrentValue = (HighValue + LowValue) / 2;
        } else if (probElectron.back() < -1e-9) {
            LowValue = CurrentValue;
            CurrentValue = (HighValue + LowValue) / 2;
        } else {
            flag = false;
        }
    }
    
    for (int i = 0; i < z.size(); ++i){
        probElectron[i] = probElectron[i] < 0 ? 0 : probElectron[i];
        probHole[i] = probHole[i] < 0 ? 0 : probHole[i];
    }
    
    std::reverse(probElectron.begin(), probElectron.end());
    std::reverse(probHole.begin(), probHole.end());
}