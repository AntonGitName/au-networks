cmake_minimum_required(VERSION 3.6)
project(ha1_testing_system)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(common)