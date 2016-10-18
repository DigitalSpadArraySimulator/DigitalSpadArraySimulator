MACRO(CORE_INCLUDE_FOLDER)
  INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/${CORE_FOLDER}/include")

  FOREACH (_header ${CORE_HEADERS})
    FILE (COPY "${CMAKE_CURRENT_SOURCE_DIR}/${CORE_FOLDER}/include/${_header}" DESTINATION "${PROJECT_BINARY_DIR}/include/Core")
    SET(CORE_INSTALL_HEADERS "${CORE_INSTALL_HEADERS}"  
                             "${CORE_FOLDER}/include/${_header}")
  ENDFOREACH ()
  
  
  FOREACH(_source ${CORE_SOURCES})
    SET (SRC_FILES ${SRC_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/${CORE_FOLDER}/src/${_source}")
  ENDFOREACH()

ENDMACRO()
