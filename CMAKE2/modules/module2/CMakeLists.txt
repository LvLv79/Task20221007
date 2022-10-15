aux_source_directory(src MODULE2_DIR1)
add_library(module2 ${MODULE2_DIR1})

target_include_directories(
    module2
    PUBLIC include)

target_link_libraries(module2 pthread)
