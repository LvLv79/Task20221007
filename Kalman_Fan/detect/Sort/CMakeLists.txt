aux_source_directory(src SORT_DIR1)
add_library(Sort SHARED ${SORT_DIR1})

find_package(OpenCV REQUIRED)


target_include_directories(
    Sort
    PUBLIC include ${OpenCV_INCLUDE_DIRS})

target_link_libraries(Sort PUBLIC ${OpenCV_LIBS})