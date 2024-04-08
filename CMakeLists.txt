cmake_minimum_required(VERSION 3.0)
project(color)

set(HEADERS src/color.h)
set(SOURCES src/main.c src/color.c)

add_executable(color ${HEADERS} ${SOURCES})
target_link_libraries(color m)