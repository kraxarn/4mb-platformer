cmake_minimum_required(VERSION 3.5)
project(4mb_platformer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB MAIN_SRC "src/*.[hc]pp")
file(GLOB SUB_SRC "src/*/*.[hc]pp")

add_executable(4mb_platformer ${MAIN_SRC} ${SUB_SRC})

target_include_directories(4mb_platformer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

include(chirp.cmake)
target_link_libraries(${PROJECT_NAME} PRIVATE chirp)

# Raylib
# (built together with chirp, but we still need the headers for now)
target_include_directories(${PROJECT_NAME} PRIVATE
	"${raylib_SOURCE_DIR}")

# CMakeRC
include(resources.cmake)
target_link_libraries(4mb_platformer PRIVATE res)
