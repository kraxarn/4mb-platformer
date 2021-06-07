#pragma once

#include "engine/scene.hpp"
#include "engine/level.hpp"
#include "engine/animatedsprite.hpp"
#include "engine/music.hpp"
#include "engine/format.hpp"
#include "engine/vector2.hpp"
#include "level/levels.hpp"

#include <memory>

class scene_level: public ce::scene
{
public:
	explicit scene_level(const ce::assets &assets);

	void render() override;

	void load(int index);

	static auto get_spawn(const ce::level &level) -> ce::vector2i;

private:
	ce::animated_sprite spr_player;
	ce::music music;

	std::unique_ptr<ce::level> level;
	ce::vector2i spawn;

	ce::tileset tiles;
	ce::tileset items;
};
