cmake_minimum_required(VERSION 3.20)
project(4mb_platformer)

set(CMAKE_CXX_STANDARD 14)

file(GLOB MAIN_SRC "src/*.[hc]pp")
file(GLOB SUB_SRC "src/*/*.[hc]pp")

add_executable(4mb_platformer ${MAIN_SRC} ${SUB_SRC})

target_include_directories(4mb_platformer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Raylib
include(raylib.cmake)
target_link_libraries(4mb_platformer PRIVATE raylib)

# CMakeRC
include(resources.cmake)
target_link_libraries(4mb_platformer PRIVATE res)
