#pragma once

#include "vec2.hpp"
#include "res.hpp"

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
		virtual auto map() const -> std::array<std::array<char, 25>, 75> = 0;

	protected:
		level() = default;
	};
}
