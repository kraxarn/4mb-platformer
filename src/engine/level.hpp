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
		virtual auto map() const -> ce::map<char> = 0;

		auto get_total_gem_count() -> int;

	protected:
		level() = default;

	private:
		int gem_count = -1;
	};
}
