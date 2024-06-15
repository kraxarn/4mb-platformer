#pragma once

#include "keymap.hpp"
#include "engine/level.hpp"
#include "engine/map.hpp"

#include "entity/boss.hpp"
#include "entity/hud.hpp"
#include "entity/leveltitle.hpp"
#include "entity/pause.hpp"
#include "entity/player.hpp"

#include <chirp/camera.hpp>
#include <chirp/handle.hpp>
#include <chirp/scene.hpp>

class scene_level: public chirp::scene
{
public:
	explicit scene_level(const chirp::assets &assets);

	void load() override;

	void update(float delta) override;

	void draw() override;

	/** Load specific level */
	void load(int index);

	/** Go to next level */
	void next_level();

private:
	static constexpr int level_width = chirp::level_tiles_width * ce::tile_size;
	static constexpr int level_height = chirp::level_tiles_height * ce::tile_size;

	// General engine stuff
	chirp::asset<chirp::music> music;
	chirp::keymap keymap;
	const chirp::assets &assets;

	// Camera
	chirp::camera camera;

	// Debug
	static constexpr int debug_hud_size = 20;
	static constexpr int debug_hud_offset = 16;
	chirp::text txt_debug;

	// Level
	std::unique_ptr<ce::level> level;
	chirp::asset<chirp::tileset> tiles;
	chirp::asset<chirp::tileset> items;

	// Entities
	chirp::handle<entity::player> entity_player;
	entity::hud entity_hud;
	entity::pause entity_pause;
	entity::level_title entity_level_title;
	std::unique_ptr<entity::boss> entity_boss;

	// Level switching
	int current_level_index = -1;
	chirp::asset<chirp::sound> snd_complete;

	void update_camera();
	void draw_map();
	void load_entities();
	void update_entities();
};
