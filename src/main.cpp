#include "colors.hpp"
#include "state.hpp"
#include "engine/draw.hpp"
#include "engine/window.hpp"
#include "enum/scenes.hpp"
#include "scene/scenelevel.hpp"

#include <chirp/assets.hpp>
#include <chirp/audio.hpp>
#include <chirp/clock.hpp>
#include <chirp/logger.hpp>
#include <chirp/os.hpp>

auto main(int /*argc*/, char **/*argv*/) -> int
{
	chirp::logger::init();

	ce::window window(1280, 720, "Tixel - 4MB Platformer");
	chirp::audio audio;

	const chirp::assets assets;
	ce::window::set_icon(assets.tileset("player")->at(1));

	if (!chirp::os::is_debug())
	{
		state::set(scene::menu, assets);
	}
	else
	{
		state::set(scene::level, assets);
		dynamic_cast<scene_level *>(state::get().get())->load(0);
	}

	while (!ce::window::should_close())
	{
		state::get()->update(chirp::clock::delta());

		window.begin();
		ce::draw::clear(color::background);
		{
			state::get()->draw();
		}
		window.end();
	}

	return 0;
}
