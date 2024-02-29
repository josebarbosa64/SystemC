cmake_minimum_required(VERSION 3.10)

project(Exercise2)

# Remember only one sc_main() function should exist.
# Choose "nand_main.cpp" here to test your NAND implementation.
# Choose "exor_main.cpp" here to test your XOR implementation.

add_executable(exercise2P3
    #nand_main.cpp
    exor_main.cpp
)

target_include_directories(exercise2P3
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(exercise2P3
    PRIVATE ${SYSTEMC_LIBRARY}
)
