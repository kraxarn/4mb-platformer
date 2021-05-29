#include "scenemenu.hpp"

scene_menu::scene_menu(const ce::assets &assets)
	: ce::scene(assets),
	font_menu(assets.font("font/menu.ttf", 20)),
	font_debug(assets.font("font/debug.ttf", 12)),
	text_menu("New game\nLoad game\nOptions\nExit game",
		16, 16, 20, color::text)
{
}

void scene_menu::render()
{
	font_menu.draw_text(text_menu);
}
