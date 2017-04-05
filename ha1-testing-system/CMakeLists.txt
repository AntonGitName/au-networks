cmake_minimum_required(VERSION 3.6)
project(ha1_testing_system)

set(CMAKE_CXX_STANDARD 11)

set(SERVER_SOURCE_FILES src/server/main.cpp)
set(CLIENT_SOURCE_FILES src/client/main.cpp src/client/main.cpp.cpp)
add_executable(ha1_testing_system_server ${SERVER_SOURCE_FILES})
add_executable(ha1_testing_system_client ${CLIENT_SOURCE_FILES})