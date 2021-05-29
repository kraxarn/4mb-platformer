#include "raylib.h"

#include "clf/clf.hpp"
#include "engine/window.hpp"
#include "engine/audio.hpp"
#include "engine/assets.hpp"

#include <sstream>
#include <vector>

auto main(int argc, char **argv) -> int
{
	ce::window window(1280, 720, "4mb-platformer");
	ce::audio audio;

	// Load levels
	ce::assets assets;
	auto levels = assets.all_levels();
	std::cout << "Loaded " << levels.size() << " levels" << std::endl;

	auto music_menu = assets.music("music/menu.xm");
	music_menu.play();

	while (!ce::window::should_close())
	{
		music_menu.update();

		BeginDrawing();
		ClearBackground(BLACK);
		{
			auto *playback = TextFormat("%.0f/%.0f",
				music_menu.played(), music_menu.length());

			DrawText(playback, 16, 16, 24, RAYWHITE);
		}
		EndDrawing();
	}

	return 0;
}
