find_package(OpenCV REQUIRED)

aux_source_directory(src RMATH_DIR1)
add_library(rmath SHARED ${RMATH_DIR1})

target_include_directories(
    rmath
    PUBLIC include ${OpenCV_INCLUDE_DIRS})