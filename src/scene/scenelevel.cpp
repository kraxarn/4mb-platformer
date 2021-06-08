#include "scenelevel.hpp"

scene_level::scene_level(const ce::assets &assets)
	: spr_player(assets.tileset("player.png")),
	music(assets.music("level1.xm")),
	items(assets.tileset("items.png")),
	tiles(assets.tileset("grass.png")),
	scene(assets)
{
	camera.set_offset(ce::vector2f(static_cast<float>(GetScreenWidth()) / 2.F,
		static_cast<float>(GetScreenHeight()) / 2.F));

	spr_player.set_scale(tile_scale);
}

void scene_level::render()
{
	camera.begin();
	music.update();

	update_input();
	update_camera();
	spr_player.draw();
	draw_map();

	camera.end();
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
	auto spawn = get_spawn(*level);
	camera.set_target(spawn * tile_size);

	// Set player position
	spr_player.set_pos(spawn * tile_size);
	spr_player.set_y(spr_player.get_y() - tile_size * 0.25F);
}

auto scene_level::get_spawn(const ce::level &level) -> ce::vector2f
{
	const auto &map = level.map();
	constexpr char spawn_index = 50;

	for (auto x = 0; x < map.size(); x++)
	{
		for (auto y = 0; y < map.at(y).size(); y++)
		{
			if (map.at(x).at(y) == spawn_index)
			{
				return {
					static_cast<float>(x),
					static_cast<float>(y)
				};
			}
		}
	}

	return {0.F, 0.F};
}

void scene_level::update_input()
{
	constexpr float step = 5.F;

	spr_player.move(input.is_down(ce::key::left)
			? -step : input.is_down(ce::key::right)
				? step : 0.F,
		input.is_down(ce::key::up)
			? -step : input.is_down(ce::key::down)
			? step : 0.F);
}

void scene_level::update_camera()
{
	camera.set_target(spr_player.get_pos());

	const auto &offset = camera.get_offset();

	const auto offset_x_min = offset.x;
	const auto offset_x_max = level_width - offset.x - tile_size * 0.25F;
	const auto offset_y_max = level_height - offset.y - tile_size * 0.25F;

	// Horizontal offset
	if (camera.get_x() < offset_x_min)
	{
		camera.set_x(offset_x_min);
	}
	else if (camera.get_x() > offset_x_max)
	{
		camera.set_x(offset_x_max);
	}

	// Vertical offset
	if (camera.get_y() > offset_y_max)
	{
		camera.set_y(offset_y_max);
	}
}

void scene_level::draw_map()
{
	const auto &map = level->map();

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
