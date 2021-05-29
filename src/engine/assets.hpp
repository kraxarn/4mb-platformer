#pragma once

#include "res.hpp"
#include "engine/level.hpp"
#include "engine/music.hpp"
#include "engine/font.hpp"

#include <vector>

namespace ce
{
	class assets
	{
	public:
		assets();

		auto level(const std::string &path) const -> ce::level;
		auto all_levels() const -> std::vector<ce::level>;

		auto music(const std::string &path) const -> ce::music;

		auto font(const std::string &path, int font_size) const -> ce::font;

	private:
		cmrc::embedded_filesystem fs;
	};
}
