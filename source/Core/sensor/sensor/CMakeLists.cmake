SET (CORE_FOLDER "sensor/sensor")
SET (CORE_HEADERS "isensor.hh"
                  "isensor_configuration.hh"
                  "isensor_factory.hh"
                  "sipm.hh"
                  "sipm_configuration.hh"
                  "sipm_configuration_factory.hh"
                  "sipm_factory.hh"
                  "spad.hh"
                  "spad_configuration.hh"
                  "spad_configuration_factory.hh"
                  "spad_factory.hh")
SET (CORE_SOURCES "isensor.cc"
                  "isensor_configuration.cc"
                  "isensor_factory.cc"
                  "sipm.cc"
                  "sipm_configuration.cc"
                  "sipm_configuration_factory.cc"
                  "sipm_factory.cc"
                  "spad.cc"
                  "spad_configuration.cc"
                  "spad_configuration_factory.cc"
                  "spad_factory.cc")

include(CoreMacroIncludeFolder.cmake)
CORE_INCLUDE_FOLDER()
