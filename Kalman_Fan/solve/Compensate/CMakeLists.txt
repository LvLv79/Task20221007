
aux_source_directory(src COMPENSATE_DIR1)
add_library(Compensate SHARED ${COMPENSATE_DIR1})

find_package(OpenCV REQUIRED)


target_include_directories(
    Compensate
    PUBLIC include ${OpenCV_INCLUDE_DIRS})

target_link_libraries(Compensate PUBLIC ${OpenCV_LIBS})

