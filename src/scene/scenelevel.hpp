#pragma once

#include "engine/scene.hpp"
#include "engine/level.hpp"
#include "engine/animatedsprite.hpp"
#include "engine/music.hpp"
#include "engine/format.hpp"
#include "engine/vector2.hpp"
#include "engine/camera.hpp"
#include "engine/input.hpp"
#include "level/levelloader.hpp"

#include <memory>

class scene_level: public ce::scene
{
public:
	explicit scene_level(const ce::assets &assets);

	void render() override;

	void load(int index);

	static auto get_spawn(const ce::level &level) -> ce::vector2f;

private:
	static constexpr float tileset_size = 18;
	static constexpr float tile_scale = 3.F;
	static constexpr float tile_size = tileset_size * tile_scale;

	static constexpr int level_tiles_width = 75;
	static constexpr int level_tiles_height = 25;
	static constexpr int level_width = level_tiles_width * tile_size;
	static constexpr int level_height = level_tiles_height * tile_size;

	ce::animated_sprite spr_player;
	ce::music music;
	ce::camera camera;
	ce::input input;

	std::unique_ptr<ce::level> level;
	ce::vector2f spawn;

	ce::tileset tiles;
	ce::tileset items;

	void update_camera();
};
