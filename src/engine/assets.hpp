#pragma once

#include <chirp/assets.hpp>
#include <chirp/font.hpp>
#include <chirp/image.hpp>
#include <chirp/level.hpp>
#include <chirp/music.hpp>
#include <chirp/sound.hpp>
#include <chirp/tileset.hpp>

namespace ce
{
	class assets
	{
	public:
		explicit assets(const chirp::assets &data);

		auto music(const std::string &path) const -> chirp::music;

		/** @note Don't use unless required */
		auto music_ptr(const std::string &path) const -> chirp::music *;

		auto sound(const std::string &path) const -> chirp::sound;

		auto font(const std::string &path, int font_size) const -> chirp::font;

		auto image(const std::string &path) const -> chirp::image;

		auto tileset(const std::string &path) const -> chirp::tileset;

		auto level(const std::string &path) const -> chirp::level;

	private:
		const chirp::assets &data;

		/** {folder}/{filename} */
		auto open(const std::string &folder,
			const std::string &filename) const -> const std::vector<unsigned char> &;
	};
}
