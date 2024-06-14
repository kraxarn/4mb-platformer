cmake_minimum_required(VERSION 3.5)
project(4mb_platformer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB MAIN_SRC "src/*.[hc]pp")
file(GLOB SUB_SRC "src/*/*.[hc]pp")

add_executable(4mb_platformer ${MAIN_SRC} ${SUB_SRC})

target_include_directories(4mb_platformer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_subdirectory(../chirp chirp)
else ()
	include(chirp.cmake)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE chirp)
