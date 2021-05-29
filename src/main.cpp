#include "engine/window.hpp"
#include "engine/audio.hpp"
#include "engine/assets.hpp"
#include "engine/draw.hpp"
#include "fmt/format.h"
#include "colors.hpp"
#include "scene/scenemenu.hpp"

#include <sstream>

auto main(int argc, char **argv) -> int
{
	ce::window window(426, 240, "4MB Platformer");
	ce::audio audio;

	// Load levels
	ce::assets assets;
	auto levels = assets.all_levels();
	std::cout << "Loaded " << levels.size() << " levels" << std::endl;

	scene_menu menu(assets);

	while (!ce::window::should_close())
	{
		ce::draw::begin();
		ce::draw::clear(color::background);
		menu.render();
		ce::draw::end();
	}

	return 0;
}
