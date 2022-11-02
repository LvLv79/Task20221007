find_package(OpenCV REQUIRED)

aux_source_directory(src TARGET_DIR1)
add_library(Target SHARED ${TARGET_DIR1})

target_include_directories(
    Target
    PUBLIC include ${OpenCV_INCLUDE_DIRS} ${Sort_INCLUDE_DIRS})

target_link_libraries(Kalman Compensate)