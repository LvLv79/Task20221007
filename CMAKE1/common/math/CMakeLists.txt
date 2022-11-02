aux_source_directory(src MATH_DIR1)
add_library(math SHARED ${MATH_DIR1})

find_package(OpenCV REQUIRED)

target_include_directories(
    math
    PUBLIC include ${OpenCV_INCLUDE_DIRS})

target_link_libraries(math PUBLIC ${OpenCV_LIBS})
