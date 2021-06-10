#include "scenelevel.hpp"

scene_level::scene_level(const ce::assets &assets)
	: scene(assets),
#ifndef NDEBUG
	fnt_debug(assets.font("debug.ttf", 22)),
	txt_debug("-", 16, 16, fnt_debug.font_size(), WHITE),
#endif
	entity_player(assets),
	music(assets.music("level1.xm")),
	items(assets.tileset("items.png")),
	tiles(assets.tileset("grass.png"))
{
	camera.set_offset(ce::vector2f(static_cast<float>(GetScreenWidth()) / 2.F,
		static_cast<float>(GetScreenHeight()) / 2.F));

	entity_player.set_scale(tile_scale);
}

void scene_level::render()
{
	camera.begin();
	music.update();

	update_input();
	update_camera();
	entity_player.draw();
	draw_map();

#ifndef NDEBUG
	physics.draw();
#endif

	camera.end();

#ifndef NDEBUG
	txt_debug.set_text(ce::fmt::format("FPS: {}\nBodies: {} ({} static, {} dynamic)",
		ce::clock::fps(), physics.bodies_count(), physics.static_bodies_count(),
		physics.dynamic_body_count()));

	fnt_debug.draw_text(txt_debug);
#endif
}

void scene_level::load(int index)
{
	physics.reset();

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
	auto spawn = get_spawn();
	camera.set_target(spawn * tile_size);

	// Load collision
	const auto &map = level->map();
	iterate_map([this, &map](int x, int y, char value)
	{
		// Only include tiles
		if (value < 0 || value >= spawn_index)
		{
			return false;
		}

		// Add physics body
		ce::vector2f pos(x, y);
		ce::vector2f size(tile_size, tile_size);
		physics.add_static_body(pos, size);

		return false;
	});

	// Set player position
	entity_player.set_pos(spawn * tile_size);
	entity_player.set_y(entity_player.get_y() - tile_size * 0.25F);
}

auto scene_level::get_spawn() const -> ce::vector2f
{
	ce::vector2f vec;

	iterate_map([&vec](int x, int y, char value)
	{
		if (value == spawn_index)
		{
			vec.x = static_cast<float>(x);
			vec.y = static_cast<float>(y);
			return true;
		}
		return false;
	});

	return vec;
}

void scene_level::iterate_map(const std::function<bool(int, int, char)> &iter) const
{
	const auto &map = level->map();

	for (auto x = 0; x < map.size(); x++)
	{
		for (auto y = 0; y < map.at(y).size(); y++)
		{
			if (iter(x, y, map.at(x).at(y)))
			{
				return;
			}
		}
	}
}

void scene_level::update_input()
{
	constexpr float step = 5.F;

	entity_player.move(input.is_down(ce::key::left)
			? -step : input.is_down(ce::key::right)
				? step : 0.F,
		input.is_down(ce::key::up)
			? -step : input.is_down(ce::key::down)
			? step : 0.F);
}

void scene_level::update_camera()
{
	camera.set_target(entity_player.get_pos());

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
	iterate_map([this](int x, int y, char tile)
	{
		// Empty tile
		if (tile < 0)
		{
			return false;
		}

		// Level tile
		if (tile < spawn_index)
		{
			tiles.draw(static_cast<float>(x) * tile_size,
				static_cast<float>(y) * tile_size,
				tile, 0.F, tile_scale);
		}

		return false;
	});
}
