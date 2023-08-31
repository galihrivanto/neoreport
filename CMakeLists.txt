cmake_minimum_required(VERSION 3.14...3.27)
      
# project setting
project(
    NeoReport 
    VERSION 1.0
    DESCRIPTION "A new report project"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CSS_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # clang intellisense 
set(PROJECT_DIR ${PROJECT_SOURCE_DIR})
set(THIRDPARTY_DIR ${PROJECT_DIR}/thirdparty)

# Boost 
find_package(Boost REQUIRED COMPONENTS program_options fiber log log_setup)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(include)

# libraries
add_subdirectory(src/core)
add_subdirectory(src/engine)

# executable app
add_subdirectory(cmd/app)
add_subdirectory(cmd/gen)
add_subdirectory(cmd/testing)

# add_subdirectory(test)
