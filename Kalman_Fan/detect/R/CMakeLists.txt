aux_source_directory(src R_DIR1)
add_library(R SHARED ${R_DIR1})

find_package(OpenCV REQUIRED)


target_include_directories(
    R
    PUBLIC include ${OpenCV_INCLUDE_DIRS})

target_link_libraries(R PUBLIC ${OpenCV_LIBS})