aux_source_directory(src M1_DIR1)
add_library(M1 SHARED ${M1_DIR1})

target_include_directories(M1 PUBLIC include)

target_link_libraries(M1 PUBLIC A1)