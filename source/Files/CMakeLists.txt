CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
include(${CMAKE_CURRENT_SOURCE_DIR}/base/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/excel/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/root/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/laser_beam/CMakeLists.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/csv/CMakeLists.cmake)
INCLUDE_DIRECTORIES ("${PROJECT_BINARY_DIR}/include/"
                     "${PROJECT_BINARY_DIR}/include/Core/")


SET( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

ADD_LIBRARY (SimulatorIO SHARED ${SRC_FILES})
TARGET_LINK_LIBRARIES(SimulatorIO Simulator)
TARGET_LINK_LIBRARIES(SimulatorIO ${FILES_LIBS})

INSTALL(TARGETS SimulatorIO
        LIBRARY DESTINATION lib
)

INSTALL(FILES ${FILES_INSTALL_HEADERS}
        DESTINATION include/Files)
