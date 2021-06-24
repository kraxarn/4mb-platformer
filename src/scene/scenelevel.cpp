#include "scenelevel.hpp"

scene_level::scene_level(const ce::assets &assets)
	: scene(assets),
#ifndef NDEBUG
	txt_debug("", debug_hud_offset, debug_hud_offset,
		debug_hud_size, WHITE),
#endif
	entity_hud(assets),
	entity_player(assets, entity_hud, ce::tile_scale),
	music(assets.music_ptr("level1.xm")),
	items(assets.tileset("items.png")),
	tiles(assets.tileset("grass.png")),
	snd_complete(assets.sound("complete.wav"))
{
	constexpr float half = 2.F;
	camera.set_offset(ce::window::size().to<float>() / half);
}

void scene_level::render()
{
	music->update();

	camera.begin();
	{
		// Update player
		if (!entity_hud.is_dead())
		{
			update_camera();
		}
		entity_player.update(input, *level);

		// Update boss
		if (entity_boss)
		{
			entity_boss->update();
		}
		update_entities();

		// Update map
		draw_map();
	}
	camera.end();

	entity_hud.draw(*level);

#ifndef NDEBUG
	txt_debug.set_text(ce::fmt::format("FPS: {}\n"
									   "Position: {}\n"
									   "Velocity: {}\n"
									   "Grounded: {}\n"
									   "Camera: X={} Y={}",
		ce::clock::fps(), entity_player.get_position(),
		entity_player.get_velocity(),
		entity_player.is_grounded(),
		camera.get_x(), camera.get_y()));

	txt_debug.draw();
#endif
}

void scene_level::load(int index)
{
	auto *new_level = level_loader::get(index);
	if (new_level == nullptr)
	{
		throw std::runtime_error(ce::fmt::format("Invalid level index: {}", index));
	}

	// Boss entity needs to be reloaded
	entity_boss.reset();

	level.reset(new_level);
	current_level_index = index;

	// Load boss if any
	load_entities();

	// Load level music
	if (level->music() != music->name())
	{
		music.reset(assets.music_ptr(ce::fmt::format("{}.xm", level->music())));
	}
	music->play();

	// Load level tiles
	tiles = assets.tileset(ce::fmt::format("{}.png", level->tileset()));

	// Load level spawn
	auto spawn = level->get_spawn();
	camera.set_target(spawn.to<float>() * ce::tile_size);
	entity_player.set_position(level->get_safe_spawn());

	// Reset HUD
	entity_hud.reset();
}

void scene_level::next_level()
{
	auto index = current_level_index + 1;

	if (!level_loader::is_valid(index))
	{
		// TODO: Go to credits screen
		throw std::runtime_error("Invalid level index");
	}

	snd_complete.play();
	load(index);
}

void scene_level::load_entities()
{
	ce::iterate_map<char>(level->map(), [this](float x, float y, char value) -> bool
	{
		// Currently, there's only one possible entity
		if (phys::collision::get_tile_type(value) == tile_type::entity
			&& value == static_cast<char>(tile::boss))
		{
			entity_boss = std::make_unique<entity::boss>(assets, entity_player,
				entity_player.get_scale());
			entity_boss->set_position(ce::vector2f(x, y) * ce::tile_size);
			return true;
		}
		return false;
	});
}

void scene_level::update_entities()
{
	if (entity_boss
		&& !entity_hud.is_dead()
		&& CheckCollisionRecs(entity_player.rect(), entity_boss->rect()))
	{
		// For some reason we kill the player from the HUD instead of from the player itself
		entity_hud.kill();

		// Easiest way to reset boss
		entity_boss.reset();
		load_entities();
	}
}

void scene_level::update_camera()
{
	camera.set_target(entity_player.get_position());

	const auto &offset = camera.get_offset();

	const auto offset_x_min = offset.x;
	const auto offset_x_max = level_width - offset.x - ce::tile_size * 0.25F;
	const auto offset_y_min = offset.y;
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
	if (camera.get_y() < offset_y_min)
	{
		camera.set_y(offset_y_min);
	}
}

void scene_level::draw_map()
{
	ce::iterate_map_all<char>(level->map(), [this](auto x, auto y, char tile)
	{
		auto tile_type = phys::collision::get_tile_type(tile);

		if (tile_type == tile_type::empty)
		{
			return;
		}

		auto x_pos = static_cast<float>(x) * ce::tile_size;
		auto y_pos = static_cast<float>(y) * ce::tile_size;

		if (tile_type == tile_type::tile
			|| tile_type == tile_type::one_way)
		{
			tiles.draw(x_pos, y_pos,
				tile, 0.F, ce::tile_scale);
		}
		else if (tile_type == tile_type::item)
		{
			if (tile != static_cast<char>(tile::exit)
				|| entity_hud.get_gem_count() == level->get_total_gem_count())
			{
				items.draw(x_pos, y_pos,
					tile % static_cast<int>(tile::spawn),
					0.F, ce::tile_scale);
			}
		}

#ifndef NDEBUG
		DrawRectangleLines(x * ce::tile_size,
			y * ce::tile_size,
			ce::tile_size,
			ce::tile_size,
			GREEN);
#endif
	});
}
