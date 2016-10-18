SET (CORE_FOLDER "sensor/quench")
SET (CORE_HEADERS "iquench.hh"
                  "quench.hh"
                  "quench_factory.hh")
SET (CORE_SOURCES "iquench.cc"
                  "quench.cc"
                  "quench_factory.cc")

include(CoreMacroIncludeFolder.cmake)
CORE_INCLUDE_FOLDER()
