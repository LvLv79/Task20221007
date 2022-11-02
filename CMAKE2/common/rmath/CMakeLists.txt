aux_source_directory(src RMATH_DIR1)
add_library(rmath SHARED ${RMATH_DIR1})

find_package(OpenCV REQUIRED)

target_include_directories(
    rmath
    PUBLIC include ${OpenCV_INCLUDE_DIRS})

target_link_libraries(rmath ${OpenCV_LIBS})