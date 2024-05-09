#include "assets.hpp"

ce::assets::assets(const chirp::assets &data)
	: data(data)
{
}

auto ce::assets::open(const std::string &folder,
	const std::string &filename) const -> const std::vector<unsigned char> &
{
	return data.load(folder, filename);
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
	return asset::sound(open("sounds", path));
}

auto ce::assets::font(const std::string &path, int font_size) const -> asset::font
{
	return asset::font(open("fonts", path), font_size);
}

auto ce::assets::image(const std::string &path) const -> asset::image
{
	return asset::image(open("images", path));
}

auto ce::assets::tileset(const std::string &path) const -> asset::tileset
{
	return asset::tileset(open("tilesets", path));
}

auto ce::assets::level(const std::string &path) const -> asset::level
{
	return asset::level(open("levels", path));
}
