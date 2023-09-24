include_directories(include)

add_library(core 
    src/log.cpp 
    src/report.cpp 
)

target_include_directories(core PUBLIC include)

target_link_libraries(core PRIVATE 
    ${Boost_LIBRARIES}
)
