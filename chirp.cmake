include(FetchContent)

FetchContent_Declare(chirp
	GIT_REPOSITORY https://github.com/kraxarn/chirp.git
	GIT_TAG main)

message(STATUS "Downloading: chirp")
FetchContent_MakeAvailable(chirp)
