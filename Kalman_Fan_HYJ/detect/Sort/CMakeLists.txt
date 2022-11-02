find_package(OpenCV REQUIRED)

aux_source_directory(src SORT_DIR1)
add_library(Sort SHARED ${SORT_DIR1})

target_include_directories(
    Sort
    PUBLIC include ${OpenCV_INCLUDE_DIRS})

set(sort_INCLUDE_DIR)
list(APPEND sort_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
list(APPEND sort_INCLUDE_DIR "${OpenCV_INCLUDE_DIRS}")

set(sort_INCLUDE_DIRS ${sort_INCLUDE_DIR}
    CACHE PATH "sort filter include directories")