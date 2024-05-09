#include "engine/window.hpp"
#include "engine/audio.hpp"
#include "engine/assets.hpp"
#include "engine/draw.hpp"
#include "colors.hpp"
#include "enum/scenes.hpp"
#include "state.hpp"

#include "chirp/assets.hpp"

auto main(int /*argc*/, char **/*argv*/) -> int
{
	ce::window window(1280, 720, "Tixel - 4MB Platformer");
	ce::audio audio;

	const chirp::assets chirp_assets;
	ce::assets assets(chirp_assets);
	ce::window::set_icon(assets.tileset("player").at(1));

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
