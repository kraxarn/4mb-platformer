#include "engine/window.hpp"
#include "engine/audio.hpp"
#include "engine/assets.hpp"
#include "engine/draw.hpp"
#include "colors.hpp"
#include "enum/scenes.hpp"
#include "state.hpp"

auto main(int argc, char **argv) -> int
{
	ce::window window(1280, 720, "4MB Platformer");
	ce::audio audio;

	ce::assets assets;
	state::set(scene::menu, assets);

	while (!ce::window::should_close())
	{
		window.begin();
		ce::draw::clear(color::background);
		{
			state::get()->render();
		}
		window.end();
	}

	return 0;
}
