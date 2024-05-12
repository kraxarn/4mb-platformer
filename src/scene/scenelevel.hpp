#pragma once

#include "engine/camera.hpp"
#include "engine/input.hpp"
#include "engine/level.hpp"
#include "engine/map.hpp"
#include "engine/scene.hpp"

#include "entity/boss.hpp"
#include "entity/hud.hpp"
#include "entity/leveltitle.hpp"
#include "entity/pause.hpp"
#include "entity/player.hpp"

class scene_level: public ce::scene
{
public:
	explicit scene_level(const ce::assets &assets);

	void render() override;

	/** Load specific level */
	void load(int index);

	/** Go to next level */
	void next_level();

private:
	static constexpr int level_width = chirp::level_tiles_width * ce::tile_size;
	static constexpr int level_height = chirp::level_tiles_height * ce::tile_size;

	// General engine stuff
	std::unique_ptr<chirp::music> music;
	ce::input input;

	// Camera
	ce::camera camera;

	// Debug
#ifndef NDEBUG
	static constexpr int debug_hud_size = 20;
	static constexpr int debug_hud_offset = 16;

	chirp::text txt_debug;
#endif

	// Level
	std::unique_ptr<ce::level> level;
	asset::tileset tiles;
	asset::tileset items;

	// Entities
	entity::player entity_player;
	entity::hud entity_hud;
	entity::pause entity_pause;
	entity::level_title entity_level_title;
	std::unique_ptr<entity::boss> entity_boss;

	// Level switching
	int current_level_index = -1;
	asset::sound snd_complete;

	void update_camera();
	void draw_map();
	void load_entities();
	void update_entities();
};
