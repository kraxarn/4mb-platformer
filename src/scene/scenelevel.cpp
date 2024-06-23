#include "scenelevel.hpp"

#include "entity/boss.hpp"
#include "entity/hud.hpp"
#include "level/levelloader.hpp"
#include "physics/collision.hpp"
#include "physics/tiles.hpp"
#include "scene/scenecredits.hpp"

#include <chirp/assets.hpp>
#include <chirp/camera.hpp>
#include <chirp/clock.hpp>
#include <chirp/collision.hpp>
#include <chirp/colors.hpp>
#include <chirp/format.hpp>
#include <chirp/os.hpp>
#include <chirp/scene.hpp>
#include <chirp/text.hpp>

#include <sstream>

void scene_level::load()
{
	snd_complete = assets().sound("complete");

	camera_main = append("cam_main", new chirp::camera());
	camera_main->set_offset(window().get_size().to<float>() / 2.F);

	text_debug = append("txt_debug", new chirp::text({},
		{debug_hud_offset, debug_hud_offset}, debug_hud_size, chirp::colors::white()));

	entity_hud = append("ent_hud", new entity::hud(assets(), window()));

	entity_player = append("cam_main/spr_player",
		new entity::player(assets(), scenes(), *entity_hud, ce::tile_scale));

	entity_map = append("cam_main/map_main", new entity::map());

	constexpr auto volume = 0.75F;
	jbx_music = append("jbx_music", new chirp::jukebox());
	jbx_music->set_volume(volume);

	entity_level_title = append("ent_lvl_title", new entity::level_title(assets(), window()));

	entity_pause = append("ent_pause", new entity::pause(assets(), window()));
}

void scene_level::update(const float delta)
{
	scene::update(delta);

	if (!entity_hud->is_dead())
	{
		update_camera();
	}

	update_entities();

	if (keymap.is_pressed("pause"))
	{
		entity_pause->set_paused(!entity_pause->get_paused());
	}

	if (chirp::os::is_debug())
	{
		std::stringstream stream;

		stream << "Debug Mode\n"
			<< "FPS:      " << chirp::clock::fps() << '\n'
			<< "Delta:    " << static_cast<int>(delta * 1000.F) << '\n'
			<< "Position: " << chirp::format("{}\n", entity_player->get_position())
			<< "Velocity: " << chirp::format("{}\n", entity_player->get_velocity())
			<< "Grounded: " << chirp::format("{}\n", entity_player->is_grounded())
			<< "Camera:   " << chirp::format("{}\n", camera_main->get_target())
			<< "Paused:   " << chirp::format("{}\n\n", entity_pause->get_paused())
			<< "Entities  (" << entities().size() << "):";

		for (const auto &name: entity_keys())
		{
			stream << '\n' << name;
		}

		text_debug->set_text(stream.str());
	}
}

void scene_level::load(int index)
{
	auto *level = level_loader::get(assets(), index);
	if (level == nullptr)
	{
		throw std::runtime_error(chirp::format("Invalid level index: {}", index));
	}

	// Boss entity needs to be reloaded
	queue_remove("cam_main/spr_boss");
	entity_boss.reset();

	entity_map->set_level(assets(), level);
	current_level_index = index;

	// Load boss if any
	load_entities();

	// Load level music
	if (jbx_music->empty() || level->music() != jbx_music->name())
	{
		const auto music = assets().music(level->music());
		jbx_music->insert(music);

		if (!chirp::os::is_debug())
		{
			jbx_music->play();
		}
	}

	// Load level spawn
	auto spawn = level->get_spawn();
	camera_main->set_target(spawn.to<float>() * ce::tile_size);
	entity_player->set_position(level->get_safe_spawn());

	// Reset HUD
	entity_hud->reset();

	// Show title
	entity_level_title->set_level(*level);
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

auto scene_level::is_paused() const -> bool
{
	return entity_pause->get_paused();
}

auto scene_level::get_keymap() const -> const ::keymap &
{
	return keymap;
}

auto scene_level::get_level() const -> ce::level *
{
	return entity_map->get_level();
}

void scene_level::load_entities()
{
	const auto *level = entity_map->get_level();

	for (const auto &tile: level->tiles())
	{
		// Currently, there's only one possible entity
		if (phys::collision::get_tile_type(tile.value) == tile_type::entity
			&& tile.value == static_cast<char>(tile::boss))
		{
			entity_boss = queue_append("cam_main/spr_boss",
				new entity::boss(assets(), entity_player->get_position(), entity_player->get_scale()));

			entity_boss->set_position(chirp::vector2<size_t>(tile.x, tile.y).to<float>() * ce::tile_size);
			entity_boss->set_lock_y(entity::boss::is_final(level));

			break;
		}
	}
}

void scene_level::update_entities()
{
	if (entity_pause->get_paused())
	{
		return;
	}

	if (!entity_boss || entity_hud->is_dead())
	{
		return;
	}

	if (!chirp::collision::check(entity_player->get_shape(), entity_boss->get_shape()))
	{
		return;
	}

	// Normal boss: Player always dies when touching
	// Final boss: Boss takes damage if hit from above, otherwise, kill player
	const auto is_final = entity::boss::is_final(entity_map->get_level());

	if (!is_final || entity_player->get_velocity().y() <= 0)
	{
		entity_hud->kill();

		// Easiest way to reset boss
		queue_remove("cam_main/spr_boss");
		load_entities();
		return;
	}

	if (entity_boss->hurt())
	{
		scenes().push<scene_credits>();
		if (const auto credits = std::dynamic_pointer_cast<scene_credits>(scenes().peek()))
		{
			credits->set_collected_coins(entity_hud->get_coin_count());
		}
		return;
	}
}

void scene_level::update_camera()
{
	camera_main->set_target(entity_player->get_position());

	const auto &offset = camera_main->get_offset();

	const auto offset_x_min = offset.x();
	const auto offset_x_max = level_width - offset.x() - ce::tile_size * 0.25F;
	const auto offset_y_min = offset.y();
	const auto offset_y_max = level_height - offset.y() - ce::tile_size * 0.25F;

	auto camera_target = camera_main->get_target();

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

	camera_main->set_target(camera_target);
}
