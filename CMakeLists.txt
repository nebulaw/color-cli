cmake_minimum_required(VERSION 3.7)

project(color)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O0 -Wall -Wextra")

add_executable(color color.c color.h)
target_link_libraries(color m)


