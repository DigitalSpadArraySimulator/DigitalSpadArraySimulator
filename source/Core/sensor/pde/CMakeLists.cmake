SET (CORE_FOLDER "sensor/pde")
SET (CORE_HEADERS "config_pde.hh"
                  "electric_field_pde.hh"
                  "junction_pde.hh"
                  "pde_behavior.hh")
SET (CORE_SOURCES "config_pde.cc"
                  "electric_field_pde.cc"
                  "junction_pde.cc"
                  "pde_behavior.cc")

include(CoreMacroIncludeFolder.cmake)
CORE_INCLUDE_FOLDER()
