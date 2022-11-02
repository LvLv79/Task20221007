set(detect_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include CACHE PATH "detect_INCLUDE_DIRS")

execute_process(COMMAND ls ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE TEST_MODULE_DETECT_ST)
string(REPLACE "\n" ";" TEST_MODULE_DETECT_ST "${TEST_MODULE_DETECT_ST}")
foreach(m ${TEST_MODULE_DETECT_ST})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${m})
        add_subdirectory(${m})
    endif()
endforeach()
