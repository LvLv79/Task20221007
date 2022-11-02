aux_source_directory(src EXCHANGE_DIR1)
add_library(exchange SHARED ${EXCHANGE_DIR1})

find_package(OpenCV REQUIRED)

target_include_directories(
    exchange
    PUBLIC include ${OpenCV_INCLUDE_DIRS})

target_link_libraries(exchange PUBLIC ${OpenCV_LIBS})