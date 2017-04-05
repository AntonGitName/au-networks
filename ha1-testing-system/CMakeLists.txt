cmake_minimum_required(VERSION 3.6)
project(ha1_testing_system)

set(CMAKE_CXX_STANDARD 11)

set(SERVER_SOURCE_FILES src/server/main.cpp)
set(CLIENT_SOURCE_FILES src/client/main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(server ${SERVER_SOURCE_FILES})
set_target_properties(server PROPERTIES COMPILE_FLAGS "-m64" LINK_FLAGS "-m64")

add_executable(client32 ${CLIENT_SOURCE_FILES})
set_target_properties(client32 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

add_executable(client64 ${CLIENT_SOURCE_FILES})
set_target_properties(client64 PROPERTIES COMPILE_FLAGS "-m64" LINK_FLAGS "-m64")