#include "scenelevel.hpp"

#include "level/levelloader.hpp"
#include "physics/tiles.hpp"
#include "scene/scenecredits.hpp"

#include <chirp/clock.hpp>
#include <chirp/collision.hpp>
#include <chirp/colors.hpp>
#include <chirp/format.hpp>
#include <chirp/os.hpp>
#include <chirp/rectangle.hpp>

scene_level::scene_level(const chirp::assets &assets)
	: scene(assets),
	txt_debug("", {debug_hud_offset, debug_hud_offset},
		debug_hud_size, chirp::colors::white()),
	entity_hud(assets, window()),
	music(assets.music("level1")),
	items(assets.tileset("items")),
	tiles(assets.tileset("grass")),
	snd_complete(assets.sound("complete")),
	entity_pause(assets, window()),
	entity_level_title(assets, window()),
	assets(assets)
{
	constexpr float half = 2.F;
	camera.set_offset(window().get_size().to<float>() / half);

	constexpr auto volume = 0.75F;
	music->set_volume(volume);
}

void scene_level::load()
{
	entity_player = std::make_unique<entity::player>(assets, scenes(), entity_hud, ce::tile_scale);
}

void scene_level::update(const float delta)
{
	if (!entity_hud.is_dead())
	{
		update_camera();
	}

	entity_player->update(keymap, *level, entity_pause.get_paused(), delta);

	if (entity_boss)
	{
		entity_boss->update(entity_pause.get_paused(), delta);
	}

	update_entities();

	if (keymap.is_pressed("pause"))
	{
		entity_pause.set_paused(!entity_pause.get_paused());
	}

	entity_level_title.update(delta);
	entity_pause.update();

	if (chirp::os::is_debug())
	{
		txt_debug.set_text(chirp::format("FPS: {}\n"
			"Delta: {} ms\n"
			"Position: {}\n"
			"Velocity: {}\n"
			"Grounded: {}\n"
			"Camera: {}\n"
			"Paused: {}",
			chirp::clock::fps(),
			static_cast<int>(delta * 1000.F),
			entity_player->get_position(),
			entity_player->get_velocity(),
			entity_player->is_grounded(),
			camera.get_target(),
			entity_pause.get_paused()));
	}
}

void scene_level::draw()
{
	music->update(*this, 0);

	camera.begin();
	{
		entity_player->draw();

		if (entity_boss)
		{
			entity_boss->draw();
		}

		draw_map();
	}
	camera.end();

	entity_hud.draw(*level);
	entity_level_title.draw();
	entity_pause.draw();

	if (chirp::os::is_debug())
	{
		txt_debug.draw();
	}
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
		music = assets.music(level->music());
	}
	music->play();

	// Load level tiles
	tiles = assets.tileset(level->tileset());

	// Load level spawn
	auto spawn = level->get_spawn();
	camera.set_target(spawn.to<float>() * ce::tile_size);
	entity_player->set_position(level->get_safe_spawn());

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

	snd_complete->play();
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
			entity_boss = std::make_unique<entity::boss>(assets, entity_player->get_position(),
				entity_player->get_scale());
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
		&& chirp::collision::check(entity_player->get_shape(), entity_boss->get_shape()))
	{
		// Normal boss: Player always dies when touching
		// Final boss: Boss takes damage if hit from above, otherwise, kill player
		auto is_final = entity::boss::is_final(level.get());

		if (!is_final
			|| entity_player->get_velocity().y() <= 0)
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
				scenes().push<scene_credits>();
				if (const auto credits = std::dynamic_pointer_cast<scene_credits>(scenes().peek()))
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
	camera.set_target(entity_player->get_position());

	const auto &offset = camera.get_offset();

	const auto offset_x_min = offset.x();
	const auto offset_x_max = level_width - offset.x() - ce::tile_size * 0.25F;
	const auto offset_y_min = offset.y();
	const auto offset_y_max = level_height - offset.y() - ce::tile_size * 0.25F;

	auto camera_target = camera.get_target();

	// Horizontal offset
	if (camera_target.x() < offset_x_min)
	{
		camera_target = chirp::vector2f(offset_x_min, camera_target.y());
	}
	else if (camera_target.x() > offset_x_max)
	{
		camera_target = chirp::vector2f(offset_x_max, camera_target.y());
	}

	// Vertical offset
	if (camera_target.y() > offset_y_max)
	{
		camera_target = chirp::vector2f(camera_target.x(), offset_y_max);
	}
	else if (camera_target.y() < offset_y_min)
	{
		camera_target = chirp::vector2f(camera_target.x(), offset_y_min);
	}

	camera->set_target(camera_target);
}
