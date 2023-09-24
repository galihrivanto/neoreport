message("cmd/neoreport")

add_executable(neoreport app.cpp)

target_compile_features(neoreport PRIVATE cxx_std_17)

target_link_libraries(neoreport PRIVATE 
    core
    NCReportEngine 
)