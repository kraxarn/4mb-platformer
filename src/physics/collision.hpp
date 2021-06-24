#pragma once

#include "engine/level.hpp"
#include "engine/vector2.hpp"
#include "physics/tiles.hpp"
#include "enum/tiletype.hpp"
#include "entity/hud.hpp"

namespace phys
{
	class collision
	{
	public:
		/** Get type of tile */
		static auto get_tile_type(char value) -> tile_type;

		/**
		 * Player is going to collide,
		 * @note Velocity is modified so player doesn't collide
		 * */
		static auto update(const Rectangle &player_rect, ce::level &level,
			ce::vector2f &velocity, entity::hud &hud) -> tile_type;

	private:
		collision() = default;

		/** How many more tiles to check around the player */
		static constexpr int offset = 4;

		/** Check if tile in rect collide in level */
		static auto will_collide(ce::level &level, entity::hud &hud,
			const ce::vector2i &tile, const Rectangle &rect,
			const ce::vector2f &velocity) -> bool;

		static auto collect_item(ce::level &level,
			entity::hud &hud, int x, int y) -> bool;
	};
}
