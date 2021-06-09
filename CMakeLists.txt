cmake_minimum_required(VERSION 3.20)
project(4mb_platformer)

set(CMAKE_CXX_STANDARD 14)

file(GLOB MAIN_SRC "src/*.[hc]pp")
file(GLOB SUB_SRC "src/*/*.[hc]pp")

if (WIN32)
	add_executable(4mb_platformer WIN32 ${MAIN_SRC} ${SUB_SRC})
else ()
	add_executable(4mb_platformer ${MAIN_SRC} ${SUB_SRC})
endif ()

target_include_directories(4mb_platformer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Raylib
include(raylib.cmake)
target_link_libraries(4mb_platformer PRIVATE raylib)

# CMakeRC
include(resources.cmake)
target_link_libraries(4mb_platformer PRIVATE res)

# Windows requires some extra stuff
if (WIN32)
	target_link_libraries(4mb_platformer PRIVATE kernel32 user32 gdi32 winmm winspool comdlg32)
	target_link_libraries(4mb_platformer PRIVATE advapi32 shell32 ole32 oleaut32 uuid odbc32)
	target_link_libraries(4mb_platformer PRIVATE odbccp32)
endif ()
