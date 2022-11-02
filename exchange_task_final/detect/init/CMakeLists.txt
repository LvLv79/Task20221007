aux_source_directory(src INIT_DIR1)
add_library(init SHARED ${INIT_DIR1})

find_package(OpenCV REQUIRED)

target_include_directories(
    init
    PUBLIC include ${OpenCV_INCLUDE_DIRS})

target_link_libraries(init PUBLIC ${OpenCV_LIBS})
