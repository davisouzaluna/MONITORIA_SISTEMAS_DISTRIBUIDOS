cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(udp_server udp_server.c)
add_executable(udp_client udp_client.c)