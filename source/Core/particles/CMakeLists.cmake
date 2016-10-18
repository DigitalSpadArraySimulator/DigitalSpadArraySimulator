SET (CORE_FOLDER "particles")
SET (CORE_HEADERS "afterpulse.hh"
                  "crosstalk.hh"
                  "dark_count.hh"
                  "particle.hh"
                  "photon.hh")
SET (CORE_SOURCES "afterpulse.cc"
                  "crosstalk.cc"
                  "dark_count.cc"
                  "particle.cc"
                  "photon.cc")

include(CoreMacroIncludeFolder.cmake)
CORE_INCLUDE_FOLDER()
