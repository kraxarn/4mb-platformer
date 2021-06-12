set(BUILD_DEMOS OFF)
set(INSTALL_DEMOS OFF)
set(BUILD_SHARED OFF)
set(BUILD_STATIC ON)
set(INSTALL_STATIC OFF)

if (POLICY CMP0077)
	cmake_policy(SET CMP0077 NEW)
endif ()

add_subdirectory(thirdparty/Chipmunk2D)
