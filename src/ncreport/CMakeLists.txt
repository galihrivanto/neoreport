message("include engine ncreport")

# ncreport 
add_subdirectory(
    ${THIRDPARTY_DIR}/ncreport_stub
    ncreport_stub
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt5
find_package(Qt5 COMPONENTS Xml Gui Widgets Sql Script Core Network REQUIRED)
include_directories(${Qt5_INCLUDE_DIRS})

include_directories(include)
include_directories(src)

add_library(engine_ncreport  
    src/engine.cpp 
)

target_include_directories(engine_ncreport PUBLIC include)

target_link_libraries(engine_ncreport PRIVATE 
    ${Qt5_LIBRARIES}
    core
    NCReport  
)