FILE (COPY "${CMAKE_CURRENT_SOURCE_DIR}/BasicExcel.hpp" 
           "${CMAKE_CURRENT_SOURCE_DIR}/ExcelFormat.h" 
      DESTINATION "${PROJECT_BINARY_DIR}/include/contrib/ExcelFormat/")

ADD_LIBRARY (ExcelFormat SHARED "${CMAKE_CURRENT_SOURCE_DIR}/BasicExcel.cpp"
                         "${CMAKE_CURRENT_SOURCE_DIR}/ExcelFormat.cpp")

INSTALL(TARGETS ExcelFormat
        LIBRARY DESTINATION lib
)

INSTALL(FILES "BasicExcel.hpp" "ExcelFormat.h"
        DESTINATION "include/contrib/ExcelFormat"
)
