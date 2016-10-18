CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (SpadSimulator)
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to RELEASE")
    set(CMAKE_BUILD_TYPE "RELEASE")
endif()

OPTION (GEN_DOXY
        "Generate the Doxygen documentation")

OPTION (VERBOSE
        "Log runtime information")
        
CONFIGURE_FILE ("${PROJECT_SOURCE_DIR}/source/build_config.hh.in" "${PROJECT_BINARY_DIR}/include/build_config.hh")

ADD_SUBDIRECTORY (${PROJECT_SOURCE_DIR}/source/contrib)
ADD_SUBDIRECTORY (${PROJECT_SOURCE_DIR}/source/Core)
ADD_SUBDIRECTORY (${PROJECT_SOURCE_DIR}/source/Files)

INCLUDE_DIRECTORIES ("${PROJECT_BINARY_DIR}/include/"
                     "${PROJECT_BINARY_DIR}/include/Core/"
                     "${PROJECT_BINARY_DIR}/include/Files/"
                     "${PROJECT_BINARY_DIR}/include/contrib/ConfigFile")


SET( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

ADD_EXECUTABLE (Timestamps main.cpp)
TARGET_LINK_LIBRARIES (Timestamps Simulator)
TARGET_LINK_LIBRARIES (Timestamps SimulatorIO)
TARGET_LINK_LIBRARIES (Timestamps ConfigFile)

IF (GEN_DOXY)
    FIND_PACKAGE(Doxygen)
    if(NOT DOXYGEN_FOUND)
        MESSAGE(FATAL_ERROR "Doxygen is needed to build the documentation. Please install it correctly")
    endif()
    configure_file(${PROJECT_SOURCE_DIR}/source/doc/doxyfile.in ${PROJECT_BINARY_DIR}/doxyfile @ONLY IMMEDIATE)
    ADD_CUSTOM_TARGET(docs          COMMAND doxygen ${PROJECT_BINARY_DIR}/doxyfile
                                    SOURCES ${PROJECT_BINARY_DIR}/doxyfile)
    ADD_DEPENDENCIES(Timestamps docs)
ENDIF (GEN_DOXY)

INSTALL(FILES "${PROJECT_BINARY_DIR}/include/build_config.hh"
        DESTINATION "include")
