find_package(OpenCV REQUIRED)

aux_source_directory(src COMPENSATE_DIR1)
add_library(Compensate SHARED ${COMPENSATE_DIR1})

target_include_directories(
    Compensate
    PUBLIC include ${OpenCV_INCLUDE_DIRS})