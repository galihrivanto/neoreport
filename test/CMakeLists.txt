# gtest 
find_package(GTest REQUIRED)
include_directories(${GTest_INCLUDE_DIR})

set(TEST_FILES
    main.cpp
    test.cpp 
)

add_executable(unit-test ${TEST_FILES})

target_link_libraries(unit-test PRIVATE
    ${GTest_LIBRARIES}
)