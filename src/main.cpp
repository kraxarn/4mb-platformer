#include "raylib.h"

#include "engine/window.hpp"
#include "engine/audio.hpp"
#include "engine/assets.hpp"
#include "engine/draw.hpp"
#include "engine/text.hpp"
#include "fmt/format.h"
#include "colors.hpp"

#include <sstream>

auto main(int argc, char **argv) -> int
{
	ce::window window(426, 240, "4MB Platformer");
	ce::audio audio;

	// Load levels
	ce::assets assets;
	auto levels = assets.all_levels();
	std::cout << "Loaded " << levels.size() << " levels" << std::endl;

	auto font_debug = assets.font("font/debug.ttf", 20);

	ce::text text_play("0/0", 16, 16, 24, color::text);

	while (!ce::window::should_close())
	{
		ce::draw::begin();
		ce::draw::clear(color::background);
		{
			text_play.set_text(fmt::format("{:4.0f}/{:4.0f}",
				music_menu.played(), music_menu.length()));
			font_debug.draw_text(text_play);
		}
		ce::draw::end();
	}

	return 0;
}
