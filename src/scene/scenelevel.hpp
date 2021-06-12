#pragma once

#include "engine/scene.hpp"
#include "engine/level.hpp"
#include "engine/animatedsprite.hpp"
#include "engine/music.hpp"
#include "engine/format.hpp"
#include "engine/vector2.hpp"
#include "engine/camera.hpp"
#include "engine/input.hpp"
#include "engine/physics.hpp"
#include "engine/staticbody.hpp"
#include "engine/clock.hpp"
#include "engine/map.hpp"
#include "level/levelloader.hpp"
#include "entity/player.hpp"

#include <memory>

class scene_level: public ce::scene
{
public:
	explicit scene_level(const ce::assets &assets);

	void render() override;

	void load(int index);

private:
	static constexpr float tileset_size = 18;
	static constexpr float tile_scale = 3.F;
	static constexpr float tile_size = tileset_size * tile_scale;

	static constexpr int level_width = ce::level_tiles_width * tile_size;
	static constexpr int level_height = ce::level_tiles_height * tile_size;

	static constexpr char spawn_index = 50;

	// General stuff
	ce::music music;
	ce::input input;
	ce::physics physics;

	// Camera
	ce::camera camera;
	ce::vector2i camera_update;

	// Debug
#ifndef NDEBUG
	ce::font fnt_debug;
	ce::text txt_debug;
#endif

	// Level
	std::unique_ptr<ce::level> level;
	ce::tileset tiles;
	ce::tileset items;

	// Entities
	player entity_player;

	/** Find spawn tile in current level */
	auto get_spawn() const -> ce::vector2f;
	/** Iterate through current level */
	void iterate_map(const std::function<bool(int x, int y, char value)> &iter) const;

	/** Is level tile */
	static auto is_tile(char value) -> bool;
	/** Player can collide with this tile */
	auto can_collide(int x, int y) const -> bool;

	void update_input();
	void update_camera();
	void update_camera_position(int x, int y);
	void draw_map();
};
