cmake_minimum_required(VERSION 3.16)

project(sockets_locais_threads)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(client client.c)
add_executable(server server.c)


target_link_libraries(client pthread uuid)
target_link_libraries(server pthread)