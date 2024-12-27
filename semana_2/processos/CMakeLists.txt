cmake_minimum_required(VERSION 3.16)

project(processos)

# versao do C
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(create_process create_process.c)
add_executable(process_states process_states.c)