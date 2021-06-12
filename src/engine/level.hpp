#pragma once

#include "res.hpp"
#include "engine/map.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <array>

/**
 * Level
 */
namespace ce
{
	class level
	{
	public:
		virtual auto name() const -> std::string = 0;
		virtual auto tileset() const -> std::string = 0;
		virtual auto music() const -> std::string = 0;
		virtual auto map() const -> ce::map<char> = 0;

	protected:
		level() = default;
	};
}
