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

auto ce::assets::music(const std::string &path) const -> ce::music
{
	return ce::music(open("music", path), path);
}

auto ce::assets::font(const std::string &path, int font_size) const -> ce::font
{
	return ce::font(open("font", path), font_size);
}

auto ce::assets::image(const std::string &path) const -> ce::image
{
	return ce::image(open("image", path));
}

auto ce::assets::tileset(const std::string &path) const -> ce::tileset
{
	return ce::tileset(open("tileset", path));
}
