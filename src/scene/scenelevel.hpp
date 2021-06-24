#pragma once

#include "asset/music.hpp"
#include "engine/scene.hpp"
#include "engine/level.hpp"
#include "engine/animatedsprite.hpp"
#include "engine/format.hpp"
#include "engine/vector2.hpp"
#include "engine/camera.hpp"
#include "engine/input.hpp"
#include "engine/clock.hpp"
#include "engine/map.hpp"
#include "engine/window.hpp"

#include "physics/tiles.hpp"
#include "physics/collision.hpp"
#include "level/levelloader.hpp"
#include "entity/player.hpp"
#include "entity/hud.hpp"

#include <memory>

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
	static constexpr int level_width = ce::level_tiles_width * ce::tile_size;
	static constexpr int level_height = ce::level_tiles_height * ce::tile_size;

	// General engine stuff
	asset::music music;
	ce::input input;

	// Camera
	ce::camera camera;

	// Debug
#ifndef NDEBUG
	static constexpr int debug_hud_size = 20;
	static constexpr int debug_hud_offset = 16;

	ce::text txt_debug;
#endif

	// Level
	std::unique_ptr<ce::level> level;
	asset::tileset tiles;
	asset::tileset items;

	// Entities
	entity::player entity_player;
	entity::hud entity_hud;

	// Level switching
	int current_level_index = -1;
	asset::sound snd_complete;

	void update_camera();
	void draw_map();
};
