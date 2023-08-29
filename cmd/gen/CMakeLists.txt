message("cmd/gen")

add_executable(gen main.cpp)

target_compile_features(gen PRIVATE cxx_std_17)

target_link_libraries(gen PRIVATE 
    core
    NCReportEngine 
)