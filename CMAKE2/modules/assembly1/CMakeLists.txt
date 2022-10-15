aux_source_directory(src ASSEMBLY1_DIR1)
add_library(assembly1 SHARED ${ASSEMBLY1_DIR1})

target_include_directories(
    assembly1
    PUBLIC include)

if(BUILD_TESTS)
    add_executable(assembly1_test test/assembly1_test.cpp)
    target_link_libraries(assembly1_test
      assembly1
    )
    add_test(NAME assembly1_test COMMAND assembly1_test)
endif()