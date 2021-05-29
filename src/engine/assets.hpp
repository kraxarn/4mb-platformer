#pragma once

#include "res.hpp"
#include "engine/level.hpp"
#include "engine/music.hpp"

#include <vector>

namespace ce
{
	class assets
	{
	public:
		assets();

		auto level(const std::string &path) -> ce::level;
		auto all_levels() -> std::vector<ce::level>;

		auto music(const std::string &path) -> ce::music;

	private:
		cmrc::embedded_filesystem fs;
	};
}
