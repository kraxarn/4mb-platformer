#pragma once

#include "engine/level.hpp"
#include "physics/tiles.hpp"

namespace phys
{
	class collision
	{
	public:
		/**
		 * Is level tile
		 */
		static auto is_tile(char value) -> bool;

		/** Player can collide with this tile */
		static auto can_collide(const ce::level &level, int x, int y) -> bool;

	private:
		collision() = default;
	};
}
