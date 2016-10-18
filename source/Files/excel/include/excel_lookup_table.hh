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
 * File        : excel_lookup_table.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Mon Apr 18 09:39:19 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef EXCEL_LOOKUP_TABLE_H
#define EXCEL_LOOKUP_TABLE_H

#include "vector.hh"

namespace YExcel {
    class BasicExcelCell;
}

/**
 * @brief Load a file and interpolate dependent parameter.
 * 
 * @warning The file should be sort on the independent parameter.
 */
class ExcelLookupTable {
private:
    ExcelLookupTable();
    ExcelLookupTable(const ExcelLookupTable&);
    ExcelLookupTable& operator=(const ExcelLookupTable&);
    
    Vector<double> keys;
    Vector<double> values;
    
    bool parseCell(const YExcel::BasicExcelCell& cell, double& out);
    
public:
    /**
     * @brief Create a lookup table base on a two column excel file.
     * 
     * @warning Only Excel 2003 format is supported.
     * 
     * @param filePath The path to the file.
     */
    ExcelLookupTable(const std::string& filePath);
    
    /**
     * @brief Destructor.
     */
    ~ExcelLookupTable();
    
    /**
     * @brief Do a linear interpolation to find the dependent parameter.
     * 
     * @param key The independent parameter.
     * @return double
     */
    double interpolateValue(const double& key) const;
};

#endif //EXCEL_LOOKUP_TABLE_H