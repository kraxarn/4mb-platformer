#pragma once

#include <chirp/level.hpp>
#include <chirp/vector2.hpp>

namespace ce
{
	class level: public chirp::level
	{
	public:
		explicit level(const chirp::level &level);

		/**
		 * Get total amount of gems in level
		 * @note Searches through the level on first run
		 */
		auto get_total_gem_count() -> int;

		/**
		 * Get player spawn point
		 * @return Level tile index
		 */
		auto get_spawn() const -> chirp::vector2i;

		/**
		 * Get safe spawn point for player
		 * @return Level absolute position
		 */
		auto get_safe_spawn() const -> chirp::vector2f;

	private:
		int gem_count = -1;
	};
}
