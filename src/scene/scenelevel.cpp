#include "scenelevel.hpp"

scene_level::scene_level(const ce::assets &assets)
	: scene(assets),
#ifndef NDEBUG
	fnt_debug(assets.font("debug.ttf", debug_hud_size)),
	txt_debug("", debug_hud_offset, debug_hud_offset,
		fnt_debug.font_size(), WHITE),
#endif
	entity_player(assets),
	music(assets.music("level1.xm")),
	items(assets.tileset("items.png")),
	tiles(assets.tileset("grass.png"))
{
	constexpr float half = 2.F;
	camera.set_offset(ce::window::size().to<float>() / half);

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
	txt_debug.set_text(ce::fmt::format("FPS: {}\n"
									   "Bodies: {} ({} static, {} dynamic)\n"
									   "CameraUpdate: {} {}",
		ce::clock::fps(), physics.bodies_count(), physics.static_bodies_count(),
		physics.dynamic_body_count(), camera_update.x, camera_update.y));

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
	ce::iterate_map_all<int, char>(level->map(), [this](int x, int y, char /*value*/)
	{
		// Add physics body
		if (can_collide(x, y))
		{
			ce::vector2i pos(x, y);
			ce::vector2f size(tile_size, tile_size);
			physics.add_static_body(pos.to<float>() * tile_size + tileset_size, size);
		}
	});

	// Set player position
	constexpr float player_tile_offset = 0.25F;
	entity_player.set_pos(spawn * tile_size);
	entity_player.set_y(entity_player.get_y() - tile_size * player_tile_offset);
}

auto scene_level::get_spawn() const -> ce::vector2f
{
	ce::vector2f vec;

	ce::iterate_map<int, char>(level->map(), [&vec](int x, int y, char value) -> bool
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

	// See if collision needs to be updated
	update_camera_position(static_cast<int>((camera.get_x() - offset.x) / tile_size),
		static_cast<int>((camera.get_y() - offset.y) / tile_size));
}

void scene_level::update_camera_position(int x, int y)
{
	if (camera_update.x == x)
	{
		return;
	}

	// Right, clear left most line
	if (camera_update.x > x)
	{

	}

	camera_update.x = x;
	camera_update.y = y;
}

void scene_level::draw_map()
{
	ce::iterate_map_all<int, char>(level->map(), [this](int x, int y, char tile)
	{
		// Empty tile
		if (tile < 0)
		{
			return;
		}

		// Level tile
		if (tile < spawn_index)
		{
			tiles.draw(static_cast<float>(x) * tile_size,
				static_cast<float>(y) * tile_size,
				tile, 0.F, tile_scale);
		}
	});
}

auto scene_level::is_tile(char value) -> bool
{
	return value >= 0 && value < spawn_index;
}

auto scene_level::can_collide(int x, int y) const -> bool
{
	const auto &map = level->map();
	const auto &value = map.at(x).at(y);

	// Only tiles require collision
	if (!is_tile(value))
	{
		return false;
	}

	// If surrounded, collision isn't required
	return !(y > 0 && is_tile(map.at(x).at(y - 1))                  // above
		&& y < map.at(x).size() - 1 && is_tile(map.at(x).at(y + 1)) // below
		&& x > 0 && is_tile(map.at(x - 1).at(y))                    // left
		&& x < map.size() - 1 && is_tile(map.at(x + 1).at(y)));     // right
}
