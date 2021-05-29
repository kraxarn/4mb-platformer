include(thirdparty/cmrc/CMakeRC.cmake)

cmrc_add_resource_library(res
	WHENCE assets
	# Levels
	assets/level/1-1.clf
	assets/level/1-2.clf
	assets/level/1-3.clf
	assets/level/1-4.clf
	assets/level/1-B.clf
	assets/level/2-1.clf
	assets/level/2-2.clf
	assets/level/2-3.clf
	assets/level/2-4.clf
	assets/level/2-B.clf
	# Music
	assets/music/level1.xm
	assets/music/level2.xm
	assets/music/menu.xm
	assets/music/boss.xm
	assets/music/credits.xm)
