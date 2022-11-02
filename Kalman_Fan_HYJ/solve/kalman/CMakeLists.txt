find_package(OpenCV REQUIRED)

aux_source_directory(src KALMAN_DIR1)
add_library(Kalman SHARED ${KALMAN_DIR1})

target_include_directories(
    Kalman
    PUBLIC include ${OpenCV_INCLUDE_DIRS})