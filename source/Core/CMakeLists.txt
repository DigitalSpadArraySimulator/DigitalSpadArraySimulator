CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

INCLUDE_DIRECTORIES ("${PROJECT_BINARY_DIR}/include")

include(${CMAKE_CURRENT_SOURCE_DIR}/algorithms/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/configurable/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/event/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/generator/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/material/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/particles/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/physics/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/sensor/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/simulator/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/utilities/CMakeLists.cmake)

SET( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

ADD_LIBRARY (Simulator SHARED ${SRC_FILES})

INSTALL(TARGETS Simulator
        LIBRARY DESTINATION lib
)

INSTALL(FILES ${CORE_INSTALL_HEADERS}
        DESTINATION "include/Core")
