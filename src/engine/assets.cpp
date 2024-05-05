#include "assets.hpp"

ce::assets::assets()
	: fs(cmrc::res::get_filesystem())
{
}

auto ce::assets::open(const std::string &folder,
	const std::string &filename) const -> cmrc::file
{
	return fs.open(ce::fmt::format("{}/{}", folder, filename));
}

auto ce::assets::music(const std::string &path) const -> asset::music
{
	return asset::music(open("music", path), path);
}

auto ce::assets::music_ptr(const std::string &path) const -> asset::music *
{
	return new asset::music(open("music", path), path);
}

auto ce::assets::sound(const std::string &path) const -> asset::sound
{
	return asset::sound(open("sound", path));
}

auto ce::assets::font(const std::string &path, int font_size) const -> asset::font
{
	return asset::font(open("font", path), font_size);
}

auto ce::assets::image(const std::string &path) const -> asset::image
{
	return asset::image(open("image", path));
}

auto ce::assets::tileset(const std::string &path) const -> asset::tileset
{
	return asset::tileset(open("tileset", path));
}

auto ce::assets::level(const std::string &path) const -> asset::level
{
	return asset::level(open("level", path));
}
