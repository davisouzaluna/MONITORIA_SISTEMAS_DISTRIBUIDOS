cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(tcp_server tcp_srv.c)
add_executable(tcp_client tcp_client.c)