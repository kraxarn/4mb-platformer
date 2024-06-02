#include "colors.hpp"
#include "scene/scenelevel.hpp"
#include "scene/scenemenu.hpp"

#include <chirp/game.hpp>
#include <chirp/os.hpp>

class game final: public chirp::game
{
public:
	game()
	{
		window().set_title("Tixel - 4MB Platformer");
		window().set_size({1280, 720});
		set_target_fps(60);
		set_clear_color(color::background);

		if (!chirp::os::is_debug())
		{
			scenes().push<scene_level>();

			const auto scene = scenes().peek();
			auto *level = dynamic_cast<scene_level *>(scene.get());
			level->load(0);
		}
		else
		{
			scenes().push<scene_menu>();
		}
	}
};

auto main(int /*argc*/, char **/*argv*/) -> int
{
	game game;
	game.run();
	return 0;
}
