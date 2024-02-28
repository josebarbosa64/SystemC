# Install script for directory: /home/josebarbosa64/SystemC

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/josebarbosa64/SystemC/not_chain/callbacks/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/clock_generator/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/custom_fifo/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/custom_signal/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/custom_tlm/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/datatypes/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/delta_delay/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/dynamic_processes/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/event_finder/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/feedback_loop/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/fifo_example/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/interfaces_ports/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/kpn_artificial_deadlock/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/kpn_example/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/multiports/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/mutex_example/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/nb_fifo_example/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/not_chain/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/portarrays/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/reporting/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/sc_event_and_queue/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/swapping_example/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/thread_example/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_at_1/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_at_2/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_at_3/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_at_4/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_at_backpressure/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_cpu_example/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_lt_debug_transport/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_lt_dmi/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_lt_initiator_interconnect_target/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_lt_initiator_target/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_memory_manager/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_multipasstrough_sockets/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_payload_extensions/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_protocol_checker/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_quantum_keeper/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/tlm_simple_sockets/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/ams-eln/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/ams-eln2/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/ams-tdf/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/ams-tdf2/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/ams-lsf/cmake_install.cmake")
  include("/home/josebarbosa64/SystemC/not_chain/ams-lsf2/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/josebarbosa64/SystemC/not_chain/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
