add_executable(testFIR_JB
    main.cpp
)

target_include_directories(testFIR_JB
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(testFIR_JB
    PRIVATE ${SYSTEMC_LIBRARY}
)
