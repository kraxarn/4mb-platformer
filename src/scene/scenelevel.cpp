#include "scenelevel.hpp"

#include "state.hpp"
#include "engine/clock.hpp"
#include "enum/scenes.hpp"
#include "level/levelloader.hpp"
#include "scene/scenecredits.hpp"

#include <chirp/format.hpp>

scene_level::scene_level(const ce::assets &assets)
	: scene(assets),
#ifndef NDEBUG
	txt_debug("", {debug_hud_offset, debug_hud_offset},
		debug_hud_size, chirp::color::white()),
#endif
	entity_hud(assets),
	entity_player(assets, entity_hud, ce::tile_scale),
	music(assets.music_ptr("level1")),
	items(assets.tileset("items")),
	tiles(assets.tileset("grass")),
	snd_complete(assets.sound("complete")),
	entity_pause(assets),
	entity_level_title(assets)
{
	constexpr float half = 2.F;
	camera.set_offset(ce::window::size().to<float>() / half);

	constexpr auto volume = 0.75F;
	music->set_volume(volume);
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
		entity_player.update(input, *level, entity_pause.get_paused());

		// Update boss
		if (entity_boss)
		{
			entity_boss->update(entity_pause.get_paused());
		}
		update_entities();

		// Update map
		draw_map();

		// Update pause
		if (input.is_pressed(ce::key::pause))
		{
			entity_pause.set_paused(!entity_pause.get_paused());
		}
	}
	camera.end();

	entity_hud.draw(*level);
	entity_level_title.update();
	entity_pause.update();

#ifndef NDEBUG
	txt_debug.set_text(chirp::format("FPS: {}\n"
									   "Position: {}\n"
									   "Velocity: {}\n"
									   "Grounded: {}\n"
									   "Camera: X={} Y={}\n"
									   "Paused: {}",
		ce::clock::fps(), entity_player.get_position(),
		entity_player.get_velocity(),
		entity_player.is_grounded(),
		camera.get_x(), camera.get_y(),
		entity_pause.get_paused()));

	txt_debug.draw();
#endif
}

void scene_level::load(int index)
{
	auto *new_level = level_loader::get(assets, index);
	if (new_level == nullptr)
	{
		throw std::runtime_error(chirp::format("Invalid level index: {}", index));
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
		music.reset(assets.music_ptr(level->music()));
	}
	music->play();

	// Load level tiles
	tiles = assets.tileset(level->tileset());

	// Load level spawn
	auto spawn = level->get_spawn();
	camera.set_target(spawn.to<float>() * ce::tile_size);
	entity_player.set_position(level->get_safe_spawn());

	// Reset HUD
	entity_hud.reset();

	// Show title
	entity_level_title.set_level(*level);
}

void scene_level::next_level()
{
	auto index = current_level_index + 1;

	if (!level_loader::is_valid(index))
	{
		index = 0;
	}

	snd_complete.play();
	load(index);
}

void scene_level::load_entities()
{
	for (const auto &tile: level->tiles())
	{
		// Currently, there's only one possible entity
		if (phys::collision::get_tile_type(tile.value) == tile_type::entity
			&& tile.value == static_cast<char>(tile::boss))
		{
			entity_boss = std::make_unique<entity::boss>(assets, entity_player,
				entity_player.get_scale());
			entity_boss->set_position(chirp::vector2<size_t>(tile.x, tile.y).to<float>() * ce::tile_size);
			entity_boss->set_lock_y(entity::boss::is_final(level.get()));
			break;
		}
	}
}

void scene_level::update_entities()
{
	if (entity_pause.get_paused())
	{
		return;
	}

	if (entity_boss
		&& !entity_hud.is_dead()
		&& CheckCollisionRecs(entity_player.rect(), entity_boss->rect()))
	{
		// Normal boss: Player always dies when touching
		// Final boss: Boss takes damage if hit from above, otherwise, kill player
		auto is_final = entity::boss::is_final(level.get());

		if (!is_final
			|| entity_player.get_velocity().y() <= 0)
		{
			entity_hud.kill();
			// Easiest way to reset boss
			entity_boss.reset();
			load_entities();
		}
		else
		{
			if (entity_boss->hurt())
			{
				state::set(::scene::credits, assets);
				auto *credits = dynamic_cast<scene_credits *>(state::get().get());
				if (credits != nullptr)
				{
					credits->set_collected_coins(entity_hud.get_coin_count());
				}
				return;
			}
		}
	}
}

void scene_level::update_camera()
{
	camera.set_target(entity_player.get_position());

	const auto &offset = camera.get_offset();

	const auto offset_x_min = offset.x();
	const auto offset_x_max = level_width - offset.x() - ce::tile_size * 0.25F;
	const auto offset_y_min = offset.y();
	const auto offset_y_max = level_height - offset.y() - ce::tile_size * 0.25F;

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
	for (const auto &tile: level->tiles())
	{
		const auto tile_type = phys::collision::get_tile_type(tile.value);
		if (tile_type == tile_type::empty)
		{
			continue;
		}

		const auto x_pos = static_cast<float>(tile.x) * ce::tile_size;
		const auto y_pos = static_cast<float>(tile.y) * ce::tile_size;

		if (tile_type == tile_type::tile
			|| tile_type == tile_type::one_way)
		{
			tiles.draw({x_pos, y_pos},
				tile.value, 0.F, ce::tile_scale);
		}
		else if (tile_type == tile_type::item)
		{
			if (tile.value != static_cast<char>(tile::exit)
				|| entity_hud.get_gem_count() == level->get_total_gem_count())
			{
				items.draw({x_pos, y_pos},
					tile.value % static_cast<int>(tile::spawn),
					0.F, ce::tile_scale);
			}
		}

#ifndef NDEBUG
		DrawRectangleLines(tile.x * ce::tile_size,
			tile.y * ce::tile_size,
			ce::tile_size,
			ce::tile_size,
			GREEN);
#endif
	}
}
