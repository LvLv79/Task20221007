aux_source_directory(src ARMOR_DIR)
add_library(Armor SHARED ${ARMOR_DIR})

target_include_directories(
    Armor
    PUBLIC include)

target_link_libraries(Armor PUBLIC kalman)