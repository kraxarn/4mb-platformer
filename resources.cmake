include(thirdparty/cmrc/CMakeRC.cmake)

cmrc_add_resource_library(res
	WHENCE assets
	# Music
	assets/music/level1.xm
	assets/music/level2.xm
	assets/music/menu.xm
	assets/music/boss.xm
	assets/music/credits.xm
	# Sound
	assets/sound/boss.wav
	assets/sound/coin.wav
	assets/sound/complete.wav
	assets/sound/fall.wav
	assets/sound/gem.wav
	assets/sound/jump.wav
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
	assets/tileset/items.png
	# Shaders
	assets/shader/grayscale.frag)
