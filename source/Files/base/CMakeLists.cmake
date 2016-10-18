SET (FILES_FOLDER  "base")
SET (FILES_HEADERS "config_importer.hh"
                   "event_importer.hh"
                   "simulation_exporter.hh")
SET (FILES_SOURCES "config_importer.cc"
                   "event_importer.cc"
                   "simulation_exporter.cc")
                  
include(FilesMacroIncludeFolder.cmake)
FILES_INCLUDE_FOLDER()
