cmake_minimum_required(VERSION 3.10)

project(Exercise4)

add_executable(exercise4P4_JB
    main.cpp
)

target_include_directories(exercise4P4_JB
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(exercise4P4_JB
    PRIVATE ${SYSTEMC_LIBRARY}
)
