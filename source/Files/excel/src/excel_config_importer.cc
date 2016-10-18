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
 * File        : excel_config_importer.cc
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 17 12:39:20 2016 -0400 by valentin
 * 
 * FILE_INFO_END */

#include "excel_config_importer.hh"

#include <BasicExcel.hpp>
#include <stdexcept>

#include "isilicon.hh"
#include "log.hh"
#include "string_cast.hh"
#include "var_type.hh"

const std::string ExcelConfigImporter::SHEET_CONSTANTS          = "Constants";
const std::string ExcelConfigImporter::SHEET_MATRIX             = "Matrix";
const std::string ExcelConfigImporter::SHEET_QUENCH             = "Quench";
const std::string ExcelConfigImporter::SHEET_SENSOR             = "Sensor";
const std::string ExcelConfigImporter::SHEET_SILICON            = "Silicon";

ExcelConfigImporter::ExcelConfigImporter(const std::string& filePath)
: ConfigImporter()
{
    silicon.clear();
    quench.clear();
    sensor.clear();
    matrix.clear();
    
    YExcel::BasicExcel xls;
    
    if (!xls.Load(filePath.c_str())) {
        throw std::logic_error("Could not open the Excel configuration file \"" + filePath + "\"");
    }
    
    parseSheet(*xls.GetWorksheet(SHEET_QUENCH.c_str()), quench);
    parseSheet(*xls.GetWorksheet(SHEET_SILICON.c_str()), silicon);
    parseSheet(*xls.GetWorksheet(SHEET_MATRIX.c_str()), matrix);
    parseSheet(*xls.GetWorksheet(SHEET_SENSOR.c_str()), sensor);
    
    xls.Close();
}

ExcelConfigImporter::ExcelConfigImporter(const string& filePath, const string& sopFilePath)
: ExcelConfigImporter(filePath)
{
    parseSOP(sopFilePath);
}


ExcelConfigImporter::~ExcelConfigImporter()
{
    silicon.clear();
    quench.clear();
    sensor.clear();
    matrix.clear();
}

std::string ExcelConfigImporter::getCellContent(const YExcel::BasicExcelCell& cell) const
{
    std::string content;
    switch (cell.Type()){
        case 0: //EMPTY
            content = "";
            break;
        case 1: //INT
            castFrom(cell.GetInteger(), content);
            break;
        case 2: //DOUBLE
            castFrom(cell.GetDouble(), content);
            break;
        case 3: //STRING
            content = cell.GetString();
            break;
        case 5: //FORMULA
            castFrom(cell.GetDouble(), content);
            break;
        default: //ELSE
            throw std::logic_error("Can't handle the Excel cell type.");
            break;
    }
    
    return content;
}

void ExcelConfigImporter::parseSheet(const YExcel::BasicExcelWorksheet& sheet, Map<std::string, std::string>& out)
{
    int rowCount = sheet.GetTotalRows();
    if (sheet.GetTotalCols() < 2) {
        throw std::logic_error("The config file must have at least two columns (PropertyName, PropertyValue).");
    }
    
    std::string PropertyName, PropertyValue;
    
    for (int i = 0; i < rowCount; ++i) {
        PropertyName = getCellContent(*sheet.Cell(i, 0));
        if (PropertyName != "") {
            PropertyValue = getCellContent(*sheet.Cell(i, 1));
            out.insert(std::pair<std::string, std::string>(PropertyName, PropertyValue));
        }
    }
}

void ExcelConfigImporter::getSiliconOpticalProperties(Vector<double>& wavelengths, Vector<double>& coefficients) const
{
    wavelengths.clear();
    coefficients.clear();

    wavelengths = this->wavelengths;
    coefficients = this->coefficients;
}

void ExcelConfigImporter::parseSOP(const std::string& filePath)
{
    YExcel::BasicExcel xls;
    YExcel::BasicExcelWorksheet* sheet;
    YExcel::BasicExcelCell* cell;
    int rowCount;
    double wavelength, coefficient;
    bool foundWavelenght, foundCoefficient;
    
    bool stop = false;
    bool open = false;
    
    if (xls.Load(filePath.c_str())) {
        open = true;
        sheet = xls.GetWorksheet(0);
    } else {
        stop = true;
        LOG_STREAM(2) << "Could not open the ops file " << filePath << std::endl; 
    }
    
    if (!stop) {
        rowCount = sheet->GetTotalRows();
        for (int i = 1; i < rowCount; ++i) {
            foundWavelenght  = parseSOPCell(*sheet->Cell(i, 0), wavelength);
            foundCoefficient = parseSOPCell(*sheet->Cell(i, 1), coefficient);
            
            if (foundCoefficient ^ foundWavelenght) {
                throw std::logic_error("Incomplete line was found in the ops file");
            } else if (foundCoefficient && foundWavelenght) {
                wavelengths.push_back(wavelength);
                coefficients.push_back(coefficient);
            }
        }
    }
    
    if (open) {
        xls.Close();
    }
}

bool ExcelConfigImporter::parseSOPCell(const YExcel::BasicExcelCell& cell, double& out)
{
    bool content = false;
    switch (cell.Type()) {
        case 1: //INT
            out = cell.GetInteger();
            content = true;
            break;
        case 2: //DOUBLE
            out = cell.GetDouble();
            content = true;
            break;
        case 0: //EMPTY
            content = false;
            break;
        default:
            throw std::logic_error("The ops file should only contain double value.");
    }
    
    return content;
}
