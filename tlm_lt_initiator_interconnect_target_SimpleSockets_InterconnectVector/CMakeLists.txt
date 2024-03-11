add_executable(tlm_lt_initiator_interconnect_target_simpleSockets_InterArray
    main.cpp
)

target_include_directories(tlm_lt_initiator_interconnect_target_simpleSockets_InterArray
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(tlm_lt_initiator_interconnect_target_simpleSockets_InterArray
    PRIVATE ${SYSTEMC_LIBRARY}
)
