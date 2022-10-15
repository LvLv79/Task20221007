find_package(OpenCV REQUIRED)

aux_source_directory(src MATH_DIR1)
add_library(math SHARED ${MATH_DIR1})

target_include_directories(
    math
    PUBLIC include ${OpenCV_INCLUDE_DIRS})
