#pragma once

#include "engine/map.hpp"
#include "physics/tiles.hpp"
#include "engine/vector2.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <array>

namespace ce
{
	class level
	{
	public:
		virtual ~level() = default;

		virtual auto name() const -> std::string = 0;
		virtual auto tileset() const -> std::string = 0;
		virtual auto music() const -> std::string = 0;
		virtual auto map() const -> const ce::map<char> & = 0;
		virtual auto type() const -> std::string = 0;

		/**
		 * Get total amount of gems in level
		 * @note Searches through the level on first run
		 */
		auto get_total_gem_count() -> int;

		/**
		 * Set tile in level
		 */
		virtual void set_tile(int x, int y, char value) = 0;

		/**
		 * Get player spawn point
		 * @return Level tile index
		 */
		auto get_spawn() const -> ce::vector2i;

		/**
		 * Get safe spawn point for player
		 * @return Level absolute position
		 */
		auto get_safe_spawn() const -> ce::vector2f;

	private:
		int gem_count = -1;
	};
}
