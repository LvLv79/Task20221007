find_package(OpenCV REQUIRED)

aux_source_directory(src FLOW_DIR1)
add_library(Flow SHARED ${FLOW_DIR1})

target_include_directories(
    Flow
    PUBLIC include ${OpenCV_INCLUDE_DIRS})