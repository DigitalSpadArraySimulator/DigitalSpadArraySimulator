INCLUDE_DIRECTORIES("$ENV{ROOTSYS}/include")

SET (FILES_FOLDER  "root")
SET (FILES_HEADERS "root_event_importer.hh"
                   "root_include_lib.hh"
                   "root_simulation_exporter.hh")
SET (FILES_SOURCES "root_event_importer.cc"
                   "root_include_lib.cc"
                   "root_simulation_exporter.cc")
                  
SET (FILES_LIBS ${FILES_LIBS} "$ENV{ROOTSYS}/lib/libCore.so"
                              "$ENV{ROOTSYS}/lib/libTree.so"
                              "$ENV{ROOTSYS}/lib/libRIO.so")

include(FilesMacroIncludeFolder.cmake)
FILES_INCLUDE_FOLDER()
