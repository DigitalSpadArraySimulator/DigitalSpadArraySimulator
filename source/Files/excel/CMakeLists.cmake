INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/include/contrib/ExcelFormat/")

SET (FILES_FOLDER  "excel")
SET (FILES_HEADERS "excel_config_importer.hh"
                   "excel_lookup_table.hh")
SET (FILES_SOURCES "excel_config_importer.cc"
                   "excel_lookup_table.cc")

SET (FILES_LIBS ${FILES_LIBS} "ExcelFormat")
                  
include(FilesMacroIncludeFolder.cmake)
FILES_INCLUDE_FOLDER()
