add_executable(testFIR_DG
    main.cpp
)

target_include_directories(testFIR_DG
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(testFIR_DG
    PRIVATE ${SYSTEMC_LIBRARY}
)
