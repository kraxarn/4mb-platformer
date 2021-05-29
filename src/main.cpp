#include "raylib.h"

#include "res.hpp"
#include "clf/clf.hpp"

#include <sstream>
#include <vector>

auto load_levels() -> std::vector<clf>
{
	std::vector<clf> levels;

	const auto fs = cmrc::res::get_filesystem();
	for (const auto &file : fs.iterate_directory("level"))
	{
		std::stringstream path;
		path << "level/" << file.filename();
		levels.emplace_back(fs.open(path.str()));
	}

	return levels;
}

auto main(int argc, char **argv) -> int
{
	InitWindow(1280, 720, "4mb-platformer");
	SetTargetFPS(60);

	auto levels = load_levels();
	std::cout << "Loaded " << levels.size() << " levels" << std::endl;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		{
			DrawText(":3", 190, 200, 20, RAYWHITE);
		}
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
