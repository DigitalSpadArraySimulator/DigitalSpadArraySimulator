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
 * File        : excel_config_importer.hh
 * Author      : Audrey Corbeil Therrien <audrey.corbeil.therrien@usherbrooke.ca>
 * Author      : Valentin Libioulle <valentin.libioulle@usherbrooke.ca>
 * Created     : Thu Mar 17 12:39:20 2016 -0400 by valentin
 * 
 * FILE_INFO_END */


#ifndef EXCEL_CONFIG_IMPORTER_EXCEL_H
#define EXCEL_CONFIG_IMPORTER_EXCEL_H

#include <string>
#include "config_importer.hh"

namespace YExcel {
    class BasicExcelWorksheet;
    class BasicExcelCell;
}

/**
 * @brief Derived ConfigImporter that reads excel file (.xls).
 * 
 * @warning This class can only read .xls files. xlsx file are not handled and will no be open.
 * Renaming the file won't change a thing since the check is done on the file signature.
 */
class ExcelConfigImporter : public ConfigImporter {
public:
    /**
     * @brief Sheet Name : "Constants"
     */
    static const std::string SHEET_CONSTANTS;
    
    /**
     * @brief Sheet Name : "Matrix"
     */
    static const std::string SHEET_MATRIX;
    
    /**
     * @brief Sheet Name : "Quench"
     */
    static const std::string SHEET_QUENCH;
    
    /**
     * @brief Sheet Name : "Sensor"
     */
    static const std::string SHEET_SENSOR;
    
    /**
     * @brief Sheet Name : "Silicon"
     */
    static const std::string SHEET_SILICON;
    
private:
    ExcelConfigImporter();
    ExcelConfigImporter(const ExcelConfigImporter&);
    ExcelConfigImporter& operator=(const ExcelConfigImporter&);
    
    Map<std::string, std::string> silicon, quench, sensor, matrix;
    Vector<double> wavelengths, coefficients;
    
    std::string getCellContent(const YExcel::BasicExcelCell& cell) const;
    void parseSheet(const YExcel::BasicExcelWorksheet& sheet, Map<std::string, std::string>& out);
    void parseSOP(const std::string& filePath);
    bool parseSOPCell(const YExcel::BasicExcelCell& cell, double& out);
    
public:
    /**
     * @brief Constructor.
     * 
     * @param filePath Path to the excel file to read (/home/bob/config.xls).
     */
    ExcelConfigImporter(const std::string& filePath);
    
    /**
     * @brief Constructor.
     * 
     * @param filePath Path to the excel file to read (/home/bob/config.xls).
     * @param sopFilePath Path to the excel file containing the Silicon Optical Properties.
     */
    ExcelConfigImporter(const std::string& filePath, const std::string& sopFilePath);
    
    /**
     * @brief Destructor.
     */
    ~ExcelConfigImporter();
    
    inline virtual const Map<std::string, std::string>& getSiliconConfig() const override {return silicon;}
    
    inline virtual const Map<std::string, std::string>& getQuenchConfig() const override {return quench;};
    
    inline virtual const Map<std::string, std::string>& getSensorConfig() const override {return sensor;}
    
    inline virtual const Map<std::string, std::string>& getMatrixConfig() const override {return matrix;}
    
    /**
     * @brief Get the silicon optical properties.
     * 
     * @warning If the alpha was not a path to an excel file, both vector will be empty.
     * 
     * @param[out] wavelengths The wavelengths.
     * @param[out] coefficients The coefficients associated to the wavelengths.
     */
    virtual void getSiliconOpticalProperties(Vector<double>& wavelengths, Vector<double>& coefficients) const override;
};

#endif //EXCEL_CONFIG_IMPORTER_EXCEL_H