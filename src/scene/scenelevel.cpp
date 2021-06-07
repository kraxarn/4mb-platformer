#include "scenelevel.hpp"

scene_level::scene_level(const ce::assets &assets)
	: spr_player(assets.tileset("player.png")),
	music(assets.music("level1.xm")),
	items(assets.tileset("items.png")),
	tiles(assets.tileset("grass.png")),
	scene(assets)
{
}

void scene_level::render()
{
	music.update();
}

void scene_level::load(int index)
{
	ce::level *new_level = nullptr;

	switch (index)
	{
		case 0:
			new_level = new level1();
			break;
		case 1:
			new_level = new level2();
			break;
		case 2:
			new_level = new level3();
			break;
		case 3:
			new_level = new level4();
			break;
		case 4:
			new_level = new level5();
			break;
		case 5:
			new_level = new level6();
			break;
		case 6:
			new_level = new level7();
			break;
		case 7:
			new_level = new level8();
			break;
		case 8:
			new_level = new level9();
			break;
		case 9:
			new_level = new level10();
			break;
	}

	if (new_level == nullptr)
	{
		throw std::runtime_error(ce::fmt::format("Invalid level index: {}", index));
	}

	level.reset(new_level);

	if (level->music() != music.name())
	{
		music = assets.music(ce::fmt::format("{}.xm", level->music()));
	}
	music.play();

	// Load level tiles
	tiles = assets.tileset(ce::fmt::format("{}.png", level->tileset()));
	// Load level spawn
	spawn = get_spawn(*level);
}

auto scene_level::get_spawn(const ce::level &level) -> ce::vector2i
{
	const auto &map = level.map();
	constexpr char spawn_index = 50;

	for (auto x = 0; x < map.size(); x++)
	{
		for (auto y = 0; y < map.at(y).size(); y++)
		{
			if (map.at(x).at(y) == spawn_index)
			{
				return {x, y};
			}
		}
	}

	return {0, 0};
}
