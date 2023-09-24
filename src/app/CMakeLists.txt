message("app")

# Qt5
find_package(Qt5 COMPONENTS Xml Gui Widgets Sql Script Core Network REQUIRED)
include_directories(${Qt5_INCLUDE_DIRS})

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
    ${Qt5_LIBRARIES}
    ${Crow_LIBRARIES}
    core
    http 
)

target_link_libraries(app PUBLIC 
    engine_ncreport
)