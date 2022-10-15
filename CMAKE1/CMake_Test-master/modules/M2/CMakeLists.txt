aux_source_directory(src M2_DIR1)
add_library(M2 SHARED ${M2_DIR1})

target_include_directories(
    M2
    PUBLIC include ${kalman_INCLUDE_DIRS})

target_link_libraries(M2 A1 A2)