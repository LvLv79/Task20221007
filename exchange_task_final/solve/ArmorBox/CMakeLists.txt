aux_source_directory(src ARMORBOX_DIR1)
add_library(ArmorBox SHARED ${ARMORBOX_DIR1})

find_package(OpenCV REQUIRED)

target_include_directories(
    ArmorBox
    PUBLIC include ${OpenCV_INCLUDE_DIRS})

target_link_libraries(ArmorBox PUBLIC ${OpenCV_LIBS})
