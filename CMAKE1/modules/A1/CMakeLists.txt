aux_source_directory(src A1_DIR1)
add_library(A1 SHARED ${A1_DIR1})

target_include_directories(
    A1
    PUBLIC include)
