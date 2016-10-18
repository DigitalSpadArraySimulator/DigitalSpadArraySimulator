SET (CORE_FOLDER "generator")
SET (CORE_HEADERS "afterpulse_generator.hh"
                  "crosstalk_generator.hh"
                  "dark_count_generator.hh"
                  "igenerator.hh")
SET (CORE_SOURCES "afterpulse_generator.cc"
                  "crosstalk_generator.cc"
                  "dark_count_generator.cc")

include(CoreMacroIncludeFolder.cmake)
CORE_INCLUDE_FOLDER()
