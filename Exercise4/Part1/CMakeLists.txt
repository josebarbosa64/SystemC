cmake_minimum_required(VERSION 3.10)

project(Exercise4)

add_executable(exercise4P1
    main.cpp
)

target_include_directories(exercise4P1
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(exercise4P1
    PRIVATE ${SYSTEMC_LIBRARY}
)
