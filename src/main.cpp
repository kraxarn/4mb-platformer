#include "colors.hpp"
#include "state.hpp"
#include "engine/draw.hpp"
#include "engine/window.hpp"
#include "enum/scenes.hpp"

#include <chirp/assets.hpp>
#include <chirp/audio.hpp>
#include <chirp/logger.hpp>

auto main(int /*argc*/, char **/*argv*/) -> int
{
	chirp::logger::init();

	ce::window window(1280, 720, "Tixel - 4MB Platformer");
	chirp::audio audio;

	const chirp::assets assets;
	ce::window::set_icon(assets.tileset("player")->at(1));

#ifdef NDEBUG
	state::set(scene::menu, assets);
#else
	state::set(scene::level, assets);
	dynamic_cast<scene_level *>(state::get().get())->load(0);
#endif

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
