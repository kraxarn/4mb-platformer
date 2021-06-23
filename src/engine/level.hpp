#pragma once

#include "res.hpp"
#include "engine/map.hpp"
#include "physics/tiles.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <array>

namespace ce
{
	class level
	{
	public:
		virtual auto name() const -> std::string = 0;
		virtual auto tileset() const -> std::string = 0;
		virtual auto music() const -> std::string = 0;
		auto map() const -> ce::map<char>;

		/**
		 * Get total amount of gems in level
		 * @note Searches through the level on first run
		 */
		auto get_total_gem_count() -> int;

		/**
		 * Set tile in level
		 */
		void set_tile(int x, int y, char value);

	protected:
		level(ce::map<char> map_data);

	private:
		int gem_count = -1;
		ce::map<char> map_data;
		bool loaded = false;
	};
}
