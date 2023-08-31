# ncreport 
add_subdirectory(
    ${THIRDPARTY_DIR}/ncreport_stub
    ncreport_stub
)

SET(SOURCES
    engine.cpp
)

include_directories(.)

add_library(NCReportEngine ${SOURCES})

target_include_directories(NCReportEngine PUBLIC 
    ${PROJECT_DIR}/include
)

target_link_libraries(NCReportEngine PRIVATE
    ${qt_LIBRARIES}
    ${Boost_LIBRARIES}
    NCReport
)
