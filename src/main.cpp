#include "engine/window.hpp"
#include "engine/audio.hpp"
#include "engine/assets.hpp"
#include "engine/draw.hpp"
#include "fmt/format.h"
#include "colors.hpp"
#include "scene/scenemenu.hpp"
#include "enum/scenes.hpp"

auto main(int argc, char **argv) -> int
{
	ce::window window(1280, 720, "4MB Platformer");
	ce::audio audio;

	ce::assets assets;
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
