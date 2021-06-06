#pragma once

#include "res.hpp"
#include "engine/level.hpp"
#include "engine/music.hpp"
#include "engine/font.hpp"
#include "engine/image.hpp"
#include "engine/tileset.hpp"

#include <vector>

namespace ce
{
	class assets
	{
	public:
		assets();

		auto music(const std::string &path) const -> ce::music;

		auto font(const std::string &path, int font_size) const -> ce::font;

		auto image(const std::string &path) const -> ce::image;

		auto tileset(const std::string &path) const -> ce::tileset;

	private:
		cmrc::embedded_filesystem fs;

		/** {folder}/{filename} */
		auto open(const std::string &folder,
			const std::string &filename) const -> cmrc::file;
	};
}
