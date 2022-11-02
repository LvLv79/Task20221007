find_package(OpenCV REQUIRED)

aux_source_directory(src R_DIR1)
add_library(R SHARED ${R_DIR1})

target_include_directories(
    R
    PUBLIC include ${OpenCV_INCLUDE_DIRS})