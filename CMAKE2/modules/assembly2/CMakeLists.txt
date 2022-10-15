find_package(OpenCV REQUIRED)

aux_source_directory(src ASSEMBLY2_DIR1)
add_library(assembly2 SHARED ${ASSEMBLY2_DIR1})

target_include_directories(
    assembly2
    PUBLIC include ${OpenCV_INCLUDE_DIRS})