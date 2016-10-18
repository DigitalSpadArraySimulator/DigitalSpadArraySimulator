SET (CORE_FOLDER "material")
SET (CORE_HEADERS "absorption_behavior.hh"
                  "constant_absorption_coefficient.hh"
                  "isilicon.hh"
                  "isilicon_factory.hh"
                  "silicon.hh"
                  "silicon_factory.hh"
                  "silicon_optical_properties.hh")
SET (CORE_SOURCES "constant_absorption_coefficient.cc"
                  "isilicon.cc"
                  "isilicon_factory.cc"
                  "silicon.cc"
                  "silicon_factory.cc"
                  "silicon_optical_properties.cc")

include(CoreMacroIncludeFolder.cmake)
CORE_INCLUDE_FOLDER()
