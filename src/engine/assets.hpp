#pragma once

#include "res.hpp"
#include "asset/music.hpp"
#include "asset/font.hpp"
#include "asset/image.hpp"
#include "asset/tileset.hpp"
#include "engine/level.hpp"
#include "engine/format.hpp"

#include <vector>

namespace ce
{
	class assets
	{
	public:
		assets();

		auto music(const std::string &path) const -> asset::music;

		auto font(const std::string &path, int font_size) const -> asset::font;

		auto image(const std::string &path) const -> asset::image;

		auto tileset(const std::string &path) const -> asset::tileset;

	private:
		cmrc::embedded_filesystem fs;

		/** {folder}/{filename} */
		auto open(const std::string &folder,
			const std::string &filename) const -> cmrc::file;
	};
}
