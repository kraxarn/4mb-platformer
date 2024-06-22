#include "scenelevel.hpp"

#include "level/levelloader.hpp"
#include "physics/collision.hpp"
#include "physics/tiles.hpp"
#include "scene/scenecredits.hpp"

#include <chirp/clock.hpp>
#include <chirp/collision.hpp>
#include <chirp/colors.hpp>
#include <chirp/entitycontainer.hpp>
#include <chirp/format.hpp>
#include <chirp/os.hpp>

#include "entity/boss.hpp"

scene_level::scene_level(const chirp::assets &assets)
	: scene(assets),
	snd_complete(assets.sound("complete")),
	entity_pause(assets, window()),
	entity_level_title(assets, window()),
	assets(assets)
{
	const auto camera = std::make_shared<chirp::camera>();
	entities().insert("cam_main", camera);
	camera->set_offset(window().get_size().to<float>() / 2.F);

	const auto txt_debug = std::make_shared<chirp::text>("", chirp::vector2i(debug_hud_offset, debug_hud_offset),
		debug_hud_size, chirp::colors::white());

	entities().insert("txt_debug", txt_debug);

	const auto ent_hud = std::make_shared<entity::hud>(assets, window());
	entities().insert("ent_hud", ent_hud);
}

void scene_level::load()
{
	const auto camera = get_camera();

	const auto ent_hud = entities().at<entity::hud>("ent_hud");
	const auto player = std::make_shared<entity::player>(assets, scenes(), *ent_hud, ce::tile_scale);
	camera->entities().insert("spr_player", player);

	const auto map = std::make_shared<entity::map>();
	camera->entities().insert("map_main", map);
}

void scene_level::update(const float delta)
{
	scene::update(delta);

	const auto &ent_hud = entities().at<entity::hud>("ent_hud");
	if (!ent_hud->is_dead())
	{
		update_camera();
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
		const auto player = get_player();
		const auto txt_debug = entities().at<chirp::text>("txt_debug");

		std::stringstream stream;

		stream << "Debug Mode\n"
			<< "FPS:      " << chirp::clock::fps() << '\n'
			<< "Delta:    " << static_cast<int>(delta * 1000.F) << '\n'
			<< "Position: " << chirp::format("{}\n", player->get_position())
			<< "Velocity: " << chirp::format("{}\n", player->get_velocity())
			<< "Grounded: " << chirp::format("{}\n", player->is_grounded())
			<< "Camera:   " << chirp::format("{}\n", get_camera()->get_target())
			<< "Paused:   " << chirp::format("{}\n\n", entity_pause.get_paused())
			<< "Entities  (" << entities().items().size() << "):";

		for (const auto &name: entities().names())
		{
			stream << '\n' << name;
		}

		txt_debug->set_text(stream.str());
	}
}

void scene_level::draw()
{
	scene::draw();

	entity_level_title.draw();
	entity_pause.draw();
}

void scene_level::load(int index)
{
	auto *level = level_loader::get(assets, index);
	if (level == nullptr)
	{
		throw std::runtime_error(chirp::format("Invalid level index: {}", index));
	}

	// Boss entity needs to be reloaded
	get_camera()->entities().erase("spr_boss");

	get_map()->set_level(assets, level);
	current_level_index = index;

	// Load boss if any
	load_entities();

	// Load level music
	if (!entities().contains("mus_main")
		|| level->music() != entities().at<chirp::music>("mus_main")->name())
	{
		constexpr auto volume = 0.75F;

		const auto music = assets.music(level->music());
		entities().erase("mus_main");
		entities().insert("mus_main", music);

		music->set_volume(volume);

		if (!chirp::os::is_debug())
		{
			music->play();
		}
	}

	// Load level spawn
	auto spawn = level->get_spawn();
	get_camera()->set_target(spawn.to<float>() * ce::tile_size);
	get_player()->set_position(level->get_safe_spawn());

	// Reset HUD
	const auto &ent_hud = entities().at<entity::hud>("ent_hud");
	ent_hud->reset();

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

auto scene_level::is_paused() const -> bool
{
	return entity_pause.get_paused();
}

auto scene_level::get_keymap() const -> const ::keymap &
{
	return keymap;
}

auto scene_level::get_level() const -> ce::level *
{
	return get_map()->get_level();
}

auto scene_level::get_player() const -> chirp::asset<entity::player>
{
	auto camera_entities = get_camera()->entities();
	return camera_entities.at<::entity::player>("spr_player");
}

auto scene_level::get_map() const -> chirp::asset<entity::map>
{
	auto camera_entities = get_camera()->entities();
	return camera_entities.at<::entity::map>("map_main");
}

auto scene_level::get_camera() const -> chirp::asset<chirp::camera>
{
	return entities().at<chirp::camera>("cam_main");
}

void scene_level::load_entities()
{
	const auto *level = get_map()->get_level();

	for (const auto &tile: level->tiles())
	{
		// Currently, there's only one possible entity
		if (phys::collision::get_tile_type(tile.value) == tile_type::entity
			&& tile.value == static_cast<char>(tile::boss))
		{
			const auto entity_player = get_player();

			const auto entity_boss = std::make_shared<entity::boss>(assets,
				entity_player->get_position(), entity_player->get_scale());

			entity_boss->set_position(chirp::vector2<size_t>(tile.x, tile.y).to<float>() * ce::tile_size);
			entity_boss->set_lock_y(entity::boss::is_final(level));

			get_camera()->entities().insert("spr_boss", entity_boss);
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

	const auto &ent_hud = entities().at<entity::hud>("ent_hud");
	auto &camera_entities = get_camera()->entities();

	if (!camera_entities.contains("spr_boss") || ent_hud->is_dead())
	{
		return;
	}

	const auto entity_player = get_player();
	const auto entity_boss = camera_entities.at<::entity::boss>("spr_boss");

	if (!chirp::collision::check(entity_player->get_shape(), entity_boss->get_shape()))
	{
		return;
	}

	// Normal boss: Player always dies when touching
	// Final boss: Boss takes damage if hit from above, otherwise, kill player
	const auto is_final = entity::boss::is_final(get_map()->get_level());

	if (!is_final || entity_player->get_velocity().y() <= 0)
	{
		ent_hud->kill();

		// Easiest way to reset boss
		camera_entities.erase("spr_boss");
		load_entities();
		return;
	}

	if (entity_boss->hurt())
	{
		scenes().push<scene_credits>();
		if (const auto credits = std::dynamic_pointer_cast<scene_credits>(scenes().peek()))
		{
			credits->set_collected_coins(ent_hud->get_coin_count());
		}
		return;
	}
}

void scene_level::update_camera()
{
	const auto camera = get_camera();
	camera->set_target(get_player()->get_position());

	const auto &offset = camera->get_offset();

	const auto offset_x_min = offset.x();
	const auto offset_x_max = level_width - offset.x() - ce::tile_size * 0.25F;
	const auto offset_y_min = offset.y();
	const auto offset_y_max = level_height - offset.y() - ce::tile_size * 0.25F;

	auto camera_target = camera->get_target();

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
