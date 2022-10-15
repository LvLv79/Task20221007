aux_source_directory(src A2_DIR1)
add_library(A2 SHARED ${A2_DIR1})

target_include_directories(
    A2
    PUBLIC include)