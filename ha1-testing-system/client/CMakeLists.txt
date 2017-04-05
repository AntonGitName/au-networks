set(SOURCE_FILES src/main.cpp src/client.cpp src/client.h)

include_directories(../common ../common/src)

add_executable(client32 ${SOURCE_FILES})
set_target_properties(client32 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
target_link_libraries(client32 common32)

add_executable(client64 ${SOURCE_FILES})
set_target_properties(client64 PROPERTIES COMPILE_FLAGS "-m64" LINK_FLAGS "-m64")
target_link_libraries(client64 common64)