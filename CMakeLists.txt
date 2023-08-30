cmake_minimum_required(VERSION 3.7)

project(color)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -O0 -Wall -Wextra -fdump-rtl-expand")

add_executable(color color.c)
target_link_libraries(color m)


