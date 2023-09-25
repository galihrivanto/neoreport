message("app")

# Crow 
find_package(Crow)
include_directories(${Crow_INCLUDE_DIRS})

include_directories(include)

add_executable(app 
    src/main.cpp
    src/app_options.cpp 
)

target_link_libraries(app PRIVATE 
    ${Boost_LIBRARIES}
    ${Crow_LIBRARIES}
    core
    http 
    engine_ncreport
)
