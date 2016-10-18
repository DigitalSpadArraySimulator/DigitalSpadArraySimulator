SET (CORE_FOLDER  "simulator")
SET (CORE_HEADERS "isimulator.hh"
                  "avalanche_simulator.hh")
SET (CORE_SOURCES "isimulator.cc"
                  "avalanche_simulator.cc")

include(CoreMacroIncludeFolder.cmake)
CORE_INCLUDE_FOLDER()
