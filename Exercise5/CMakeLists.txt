cmake_minimum_required(VERSION 3.10)

project(Exercise5)

add_executable(exercise5
    main.cpp
    kpn.cpp
)

target_include_directories(exercise5
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(exercise5
    PRIVATE ${SYSTEMC_LIBRARY}
)
