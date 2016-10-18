SET (CORE_FOLDER  "sensor/matrix")
SET (CORE_HEADERS "isensor_matrix.hh"
                  "isensor_matrix_factory.hh"
                  "sipm_matrix.hh"
                  "sipm_matrix_factory.hh"
                  "spad_matrix.hh"
                  "spad_matrix_factory.hh")
SET (CORE_SOURCES "isensor_matrix.cc"
                  "isensor_matrix_factory.cc"
                  "sipm_matrix.cc"
                  "sipm_matrix_factory.cc"
                  "spad_matrix.cc"
                  "spad_matrix_factory.cc")

include(CoreMacroIncludeFolder.cmake)
CORE_INCLUDE_FOLDER()
