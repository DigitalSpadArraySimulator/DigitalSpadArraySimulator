SET (CORE_FOLDER "utilities")
SET (CORE_HEADERS "position.hh"
                  "coordinate.hh"
                  "differential_equation.hh"
                  "log.hh"
                  "map.hh"
                  "map.hpp"
                  "ptr_ref.hh"
                  "random.hh"
                  "stochastic.hh"
                  "string_cast.hh"
                  "string_cast.hpp"
                  "var_type.hh"
                  "var_type.hpp"
                  "vector.hh"
                  "vector.hpp")
SET (CORE_SOURCES "log.cc"
                  "position.cc"
                  "coordinate.cc"
                  "differential_equation.cc"
                  "random.cc"
                  "stochastic.cc"
                  "string_cast.cc"
                  "var_type.cc")

include(CoreMacroIncludeFolder.cmake)
CORE_INCLUDE_FOLDER()