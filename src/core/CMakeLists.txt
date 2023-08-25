set(SOURCES
    log.cpp
)

add_library(core ${SOURCES})

target_include_directories(core PUBLIC $PROJECT_DIR/include)

target_link_libraries(core PRIVATE 
    ${Boost_LIBRARIES}
)
