include(thirdparty/cmrc/CMakeRC.cmake)

cmrc_add_resource_library(res
	WHENCE assets
	# Music
	assets/music/level1.xm
	assets/music/level2.xm
	assets/music/menu.xm
	assets/music/boss.xm
	assets/music/credits.xm
	# Fonts
	assets/font/menu.ttf
	assets/font/submenu.ttf
	# Images
	assets/image/arrow.png
	# Tileset
	assets/tileset/player.png
	assets/tileset/grass.png
	assets/tileset/dirt.png
	assets/tileset/enemy.png
	assets/tileset/hud.png
	assets/tileset/items.png)
