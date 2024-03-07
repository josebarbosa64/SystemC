cmake_minimum_required(VERSION 3.10)

project(Exercise8)

add_executable(exercise8
    main.cpp
    initiator.h
    target.h
    memory_manager.cpp
    memory_manager.h
    util.h
    tlm2_base_protocol_checker.h
)

target_include_directories(exercise8
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(exercise8
    PRIVATE ${SYSTEMC_LIBRARY}
)
