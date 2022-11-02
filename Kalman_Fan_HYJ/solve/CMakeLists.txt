set(solve_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include CACHE PATH "solve_INCLUDE_DIRS")

execute_process(COMMAND ls ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE TEST_MODULE_SOLVE_ST)
string(REPLACE "\n" ";" TEST_MODULE_SOLVE_ST "${TEST_MODULE_SOLVE_ST}")
foreach(m ${TEST_MODULE_SOLVE_ST})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${m})
        add_subdirectory(${m})
    endif()
endforeach()
