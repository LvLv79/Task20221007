aux_source_directory(src KALMAN_DIR)
add_library(kalman SHARED ${KALMAN_DIR})

find_package(OpenCV REQUIRED)

target_include_directories(
    kalman
    PUBLIC include ${OpenCV_INCLUDE_DIRS})

target_link_libraries(kalman PUBLIC ${OpenCV_LIBS})