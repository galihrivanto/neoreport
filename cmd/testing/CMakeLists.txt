# message("cmd/testing")

# # ncreport 
# add_subdirectory(
#     ${THIRDPARTY_DIR}/ncreport_stub
#     ncreport_stub
# )

# add_executable(testing main.cpp)


# target_link_libraries(testing PRIVATE
#     ${qt_LIBRARIES}
#     NCReport
# )


message("cmd/testing")

project(Qthread_testing)

# ncreport 
add_subdirectory(
    ${THIRDPARTY_DIR}/ncreport_stub
    ncreport_stub
)

include_directories(".")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS Xml Gui Widgets Sql Script Core Network REQUIRED)
include_directories(${Qt5_INCLUDE_DIRS})

find_package(fmt REQUIRED)

add_executable(testing worker.cpp main.cpp)

target_link_libraries(testing PRIVATE
    NCReport
    ${Qt5_LIBRARIES}
    fmt::fmt
)