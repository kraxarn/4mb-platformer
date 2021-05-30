#include "engine/window.hpp"
#include "engine/audio.hpp"
#include "engine/assets.hpp"
#include "engine/draw.hpp"
#include "fmt/format.h"
#include "colors.hpp"
#include "scene/scenemenu.hpp"
#include "enum/scenes.hpp"

#include <sstream>

auto main(int argc, char **argv) -> int
{
	ce::window window(1280, 720, "4MB Platformer");
	ce::audio audio;

	// Load levels
	ce::assets assets;
	auto levels = assets.all_levels();
	std::cout << "Loaded " << levels.size() << " levels" << std::endl;

	std::map<scene, std::shared_ptr<ce::scene>> scenes{
		{scene::menu, std::make_shared<scene_menu>(assets)},
	};

	while (!ce::window::should_close())
	{
		window.begin();
		ce::draw::clear(color::background);
		{
			scenes.at(scene::menu)->render();
		}
		window.end();
	}

	return 0;
}
