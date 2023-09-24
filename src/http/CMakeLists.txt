message("http api")

# Crow 
find_package(Crow)
include_directories(${Crow_INCLUDE_DIRS})

include_directories(include)

add_library(http 
    src/handler.cpp 
)

target_include_directories(http PUBLIC include)

target_link_libraries(http PRIVATE
    ${Crow_LIBRARIES}
    core 
)