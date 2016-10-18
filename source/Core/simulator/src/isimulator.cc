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
 * File        : isimulator.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Tue Apr 5 13:27:30 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "isimulator.hh"

#include "iconfigurable_factory.hh"
#include "iquench.hh"
#include "isensor_matrix.hh"
#include "isensor_matrix_factory.hh"
#include "isilicon.hh"
#include "isilicon_factory.hh"


ISimulator::ISimulator()
: quench(0)
, matrix(0)
, silicon(0)
, quenchFactory(0)
, matrixFactory(0)
, siliconFactory(0)
{}

ISimulator::~ISimulator()
{
    if (quench){
        delete quench;
    }
    if (quenchFactory) {
        delete quenchFactory;
    }
    if(matrix) {
        delete matrix;
    }
    if (matrixFactory){
        delete matrixFactory;
    }
    if (silicon) {
        delete silicon;
    }
    if (siliconFactory){
        delete siliconFactory;
    }
}

void ISimulator::setQuenchFactory(IConfigurableFactory<IQuench>* quenchFactory)
{
    if (!quenchFactory) {
        throw std::invalid_argument("The given IConfigurableFactory<IQuench> is null");
    }
    
    if (this->quenchFactory != quenchFactory){
        if (this->quenchFactory){
            delete this->quenchFactory;
        }
        this->quenchFactory = quenchFactory;
        
        if (quench){
            delete quench;
            quench = 0;
        }
    }
}

void ISimulator::setSensorMatrixFactory(ISensorMatrixFactory* matrixFactory)
{
    if (!matrixFactory) {
        throw std::invalid_argument("The given ISensorMatrixFactory is null");
    }
    
    if (this->matrixFactory != matrixFactory){
        if (this->matrixFactory){
            delete this->matrixFactory;
        }
        this->matrixFactory = matrixFactory;
        
        if (matrix){
            delete matrix;
            matrix = 0;
        }
    }
    
    this->matrixFactory->setSimulator(this);
}

void ISimulator::setSiliconFactory(ISiliconFactory* siliconFactory)
{
    if (!siliconFactory) {
        throw std::invalid_argument("The given ISiliconFactory is null");
    }
    
    if (this->siliconFactory != siliconFactory){
        if (this->siliconFactory){
            delete this->siliconFactory;
        }
        this->siliconFactory = siliconFactory;
        
        if (silicon){
            delete silicon;
            silicon = 0;
        }
    }
}

void ISimulator::init(const Map<std::string, std::string>& siliconProperties, 
                      const Map<std::string, std::string>& quenchProperties, 
                      const Map<std::string, std::string>& spadProperties, 
                      const Map<std::string, std::string>& matrixProperties)
{
    if (silicon || quench || matrix) {
        throw std::logic_error("The simulator was already initialized");
    }
    
    silicon = siliconFactory->build(siliconProperties);
    quench = quenchFactory->build(quenchProperties);
    matrix = matrixFactory->build(matrixProperties, spadProperties);
}

void ISimulator::resetMatrix()
{
    matrix->reset();
}
