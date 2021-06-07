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

	const auto &map = level->map();

	constexpr float tile_scale = 2.F;
	constexpr int tile_size = 18 * tile_scale;

	for (auto x = 0; x < map.size(); x++)
	{
		for (auto y = 0; y < map.at(y).size(); y++)
		{
			const auto &tile = map.at(x).at(y);

			// Empty tile
			if (tile < 0)
			{
				continue;
			}

			// Level tile
			if (tile < 50)
			{
				tiles.draw(x * tile_size, y * tile_size, tile, 0.F, tile_scale);
			}
		}
	}
}

void scene_level::load(int index)
{
	auto *new_level = level_loader::get(index);
	if (new_level == nullptr)
	{
		throw std::runtime_error(ce::fmt::format("Invalid level index: {}", index));
	}

	level.reset(new_level);

	// Load level music
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
