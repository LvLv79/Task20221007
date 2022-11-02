find_package(OpenCV REQUIRED)

aux_source_directory(src/module1a MODULE1_DIR1)
aux_source_directory(src/module1b MODULE1_DIR2)

if(BUILD_A)
    add_library(module1 SHARED ${MODULE1_DIR1})
    target_include_directories(
        module1 PUBLIC include)
    
    target_link_libraries(module1 assembly1 assembly2)
endif()

if(BUILD_B)
    add_library(module1 SHARED ${MODULE1_DIR2})
    target_include_directories(
        module1 PUBLIC include)
    
    target_link_libraries(module1 assembly1 assembly2)
endif()

