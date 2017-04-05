set(SOURCE_FILES src/tcp_accepted_socket.cpp src/tcp_server_socket.cpp
        src/network_exception.cpp src/tcp_client_socket.cpp
        src/util.cpp
        src/protocol.cpp
        src/serializable.cpp)

add_library(common64 ${SOURCE_FILES})
set_target_properties(common64 PROPERTIES COMPILE_FLAGS "-m64" LINK_FLAGS "-m64")

add_library(common32 ${SOURCE_FILES})
set_target_properties(common32 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")