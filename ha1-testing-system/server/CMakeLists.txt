set(SOURCE_FILES src/main.cpp src/server.cpp src/server.h)

include_directories(../common ../common/src)

add_executable(server ${SOURCE_FILES})
set_target_properties(server PROPERTIES COMPILE_FLAGS "-m64" LINK_FLAGS "-m64")
target_link_libraries(server common64 pthread)