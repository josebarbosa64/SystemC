cmake_minimum_required(VERSION 3.10)

project(Exercise6)

add_executable(exercise6P3
    main.cpp
    memory.h
    processor.h
    bus.h
    
    stimuli1.txt
    stimuli2.txt
)

target_include_directories(exercise6P3
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(exercise6P3
    PRIVATE ${SYSTEMC_LIBRARY}
)
