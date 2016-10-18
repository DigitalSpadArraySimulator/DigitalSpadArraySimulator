FILE (COPY "${CMAKE_CURRENT_SOURCE_DIR}/ConfigFile.h" 
      DESTINATION "${PROJECT_BINARY_DIR}/include/contrib/ConfigFile/")

ADD_LIBRARY (ConfigFile SHARED "${CMAKE_CURRENT_SOURCE_DIR}/ConfigFile.cc")

INSTALL(TARGETS ConfigFile
        LIBRARY DESTINATION lib
)

INSTALL(FILES "ConfigFile.h"
        DESTINATION "include/contrib/ConfigFile"
)