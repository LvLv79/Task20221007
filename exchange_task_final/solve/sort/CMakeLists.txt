aux_source_directory(src SORT_DIR1)
add_library(sort SHARED ${SORT_DIR1})

find_package(OpenCV REQUIRED)

target_include_directories(
    sort
    PUBLIC include ${OpenCV_INCLUDE_DIRS})

target_link_libraries(sort PUBLIC ${OpenCV_LIBS})
