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

	static constexpr int level_tiles_width = 75;
	static constexpr int level_tiles_height = 25;
	static constexpr int level_width = level_tiles_width * tile_size;
	static constexpr int level_height = level_tiles_height * tile_size;

	static constexpr char spawn_index = 50;

	ce::music music;
	ce::camera camera;
	ce::input input;
	ce::physics physics;

#ifndef NDEBUG
	ce::font fnt_debug;
	ce::text txt_debug;
#endif

	std::unique_ptr<ce::level> level;

	ce::tileset tiles;
	ce::tileset items;

	player entity_player;

	auto get_spawn() const -> ce::vector2f;
	void iterate_map(const std::function<bool(int x, int y, char value)> &iter) const;

	void update_input();
	void update_camera();
	void draw_map();
};
