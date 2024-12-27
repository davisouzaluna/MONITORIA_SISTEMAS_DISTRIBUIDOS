cmake_minimum_required(VERSION 3.16)

project(threads)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(SOURCES
    multithread.c
    thread_simples.c
    mutex_wrong.c
    mutex_correct.c
    deadlock.c
    deadlock_resolved.c
)

foreach(SOURCE ${SOURCES})
    get_filename_component(EXECUTABLE ${SOURCE} NAME_WE)
    add_executable(${EXECUTABLE} ${SOURCE})
    target_link_libraries(${EXECUTABLE} pthread)
endforeach()
