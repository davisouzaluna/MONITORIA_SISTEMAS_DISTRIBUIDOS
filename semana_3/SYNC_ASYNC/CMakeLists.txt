cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")

add_executable(sync_server sync_srv.c)
add_executable(async_server async_srv.c)