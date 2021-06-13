#include "scenelevel.hpp"

scene_level::scene_level(const ce::assets &assets)
	: scene(assets),
#ifndef NDEBUG
	txt_debug("", debug_hud_offset, debug_hud_offset,
		debug_hud_size, WHITE),
#endif
	entity_player(assets, physics, ce::tile_scale),
	music(assets.music("level1.xm")),
	items(assets.tileset("items.png")),
	tiles(assets.tileset("grass.png"))
{
	constexpr float half = 2.F;
	camera.set_offset(ce::window::size().to<float>() / half);
}

void scene_level::render()
{
	camera.begin();
	music.update();

	update_input();
	update_camera();
	entity_player.draw();
	draw_map();

	physics.update(ce::clock::frame_time());
#ifndef NDEBUG
	physics.debug_draw();
#endif

	camera.end();

#ifndef NDEBUG
	txt_debug.set_text(ce::fmt::format("FPS: {}\n"
									   "Bodies: static={}, dynamic={}\n",
		ce::clock::fps(), physics.static_bodies_count(),
		physics.dynamic_body_count()));

	txt_debug.draw();
#endif
}

void scene_level::load(int index)
{
	physics.clear_static();

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
	camera.set_target(spawn * ce::tile_size);

	// Load collision
	ce::iterate_map_all<char>(level->map(), [this](auto x, auto y, char /*value*/)
	{
		// Add physics body
		if (can_collide(x, y))
		{
			ce::vector2i pos(x, y);
			ce::vector2f size(ce::tile_size, ce::tile_size);
			physics.add_static_body(size, pos.to<float>() * ce::tile_size + ce::tileset_size);
		}
	});

	// Set player position
	constexpr float player_tile_offset = 0.25F;
	ce::vector2f player_position = spawn * ce::tile_size;
	player_position.y = player_position.y - ce::tile_size * player_tile_offset;
	entity_player.set_position(player_position);
}

auto scene_level::get_spawn() const -> ce::vector2f
{
	ce::vector2f vec;

	ce::iterate_map<char>(level->map(), [&vec](auto x, auto y, char value) -> bool
	{
		if (value == spawn_index)
		{
			vec = ce::vector2<std::size_t>(x, y).to<float>();
			return true;
		}
		return false;
	});

	return vec;
}

void scene_level::update_input()
{
	auto x = 0;
	if (input.is_down(ce::key::left))
	{
		x--;
	}
	if (input.is_down(ce::key::right))
	{
		x++;
	}
	entity_player.move(x);

	if (input.is_pressed(ce::key::jump))
	{
		entity_player.jump();
	}
}

void scene_level::update_camera()
{
	camera.set_target(entity_player.position());

	const auto &offset = camera.get_offset();

	const auto offset_x_min = offset.x;
	const auto offset_x_max = level_width - offset.x - ce::tile_size * 0.25F;
	const auto offset_y_max = level_height - offset.y - ce::tile_size * 0.25F;

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
	ce::iterate_map_all<char>(level->map(), [this](auto x, auto y, char tile)
	{
		// Empty tile
		if (tile < 0)
		{
			return;
		}

		// Level tile
		if (tile < spawn_index)
		{
			tiles.draw(static_cast<float>(x) * ce::tile_size,
				static_cast<float>(y) * ce::tile_size,
				tile, 0.F, ce::tile_scale);
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
