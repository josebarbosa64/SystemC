add_executable(testFIR
    main.cpp
)

target_include_directories(testFIR
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(testFIR
    PRIVATE ${SYSTEMC_LIBRARY}
)
