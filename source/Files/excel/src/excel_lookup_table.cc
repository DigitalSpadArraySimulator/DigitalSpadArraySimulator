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
 * File        : excel_lookup_table.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Mon Apr 18 09:39:19 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#include "excel_lookup_table.hh"

#include <BasicExcel.hpp>

#include "array_algorithm.hh"

ExcelLookupTable::ExcelLookupTable(const std::string& filePath)
: keys()
, values()
{
    YExcel::BasicExcel xls;
    YExcel::BasicExcelWorksheet* sheet;
    int rowCount;
    double key, value;
    bool foundKey, foundValue;
    
    if (!xls.Load(filePath.c_str())) {
        throw std::logic_error("Could not open the Excel lookup table file \"" + filePath + "\"");
    }
    
    sheet = xls.GetWorksheet(0);
    rowCount = sheet->GetTotalRows();
    for (int i = 1; i < rowCount; ++i) {
        foundKey = parseCell(*sheet->Cell(i, 0), key);
        foundValue = parseCell(*sheet->Cell(i, 1), value);
        
        if (foundKey ^ foundValue) {
            throw std::logic_error("Incomplete line was found in the lookup table file");
        } else if (foundKey && foundValue) {
            keys.push_back(key);
            values.push_back(value);
        }
    }
    
    xls.Close();
}

ExcelLookupTable::~ExcelLookupTable()
{
    keys.clear();
    values.clear();
}

bool ExcelLookupTable::parseCell(const YExcel::BasicExcelCell& cell, double& out)
{
    bool content = false;
    switch (cell.Type()) {
        case 1: //INT
            out = cell.GetInteger();
            content = true;
            break;
        case 5: //FORMULA
        case 2: //DOUBLE
            out = cell.GetDouble();
            content = true;
            break;
        case 0: //EMPTY
            content = false;
            break;
        default:
            throw std::logic_error("The lookup table file should only contains double value.");
    }
    
    return content;
}

double ExcelLookupTable::interpolateValue(const double& key) const
{
    double value = 0;
    if (keys.size() == 0) {
        throw std::logic_error("There are no keys in the lookup table.");
    } else if (keys.size() == 1) {
        value = values[0];
    } else {
        int idx1, idx2;
        double a, b;
        idx1 = Dichotomic::findSmallerClosestIndex(keys, key);
        if (idx1 == keys.size() -1) {
            idx2 = idx1;
            --idx1;
        } else {
            idx2 = idx1 + 1;
        }
        a = (values[idx2] - values[idx1]) / (keys[idx2] - keys[idx1]);
        b = values[idx1] - a * keys[idx1];
        value = a * key + b;
    }

    return value;
}
