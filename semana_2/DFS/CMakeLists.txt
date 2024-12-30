
cmake_minimum_required(VERSION 3.16)

project(DistributedFileSystem)
set(CMAKE_C_STANDARD 11)

set(SOURCES_SERVER
    server.c
    file_system.c
)

set(SOURCES_CLIENT
    client.c
    file_system.c
)
add_executable(server ${SOURCES_SERVER})
add_executable(client ${SOURCES_CLIENT})

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
