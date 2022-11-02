aux_source_directory(src TARGET_DIR1)
add_library(Target SHARED ${TARGET_DIR1})

target_include_directories(
    Target
    PUBLIC include)

target_link_libraries(Target PUBLIC kalman Compensate Sort)