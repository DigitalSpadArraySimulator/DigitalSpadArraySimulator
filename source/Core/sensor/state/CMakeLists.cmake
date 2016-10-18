SET (CORE_FOLDER  "sensor/state")

SET (CORE_HEADERS "charging_state.hh"
                  "quenching_state.hh"
                  "ready_state.hh"
                  "state.hh")
SET (CORE_SOURCES "charging_state.cc"
                  "quenching_state.cc"
                  "ready_state.cc"
                  "state.cc")

include(CoreMacroIncludeFolder.cmake)
CORE_INCLUDE_FOLDER()