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

auto ce::assets::music(const std::string &path) const -> chirp::music
{
	return chirp::music(open("music", path), path);
}

auto ce::assets::music_ptr(const std::string &path) const -> chirp::music *
{
	return new chirp::music(open("music", path), path);
}

auto ce::assets::sound(const std::string &path) const -> chirp::sound
{
	return chirp::sound(open("sounds", path));
}

auto ce::assets::font(const std::string &path, const int font_size) const -> chirp::font
{
	return chirp::font(open("fonts", path), font_size);
}

auto ce::assets::image(const std::string &path) const -> chirp::image
{
	return chirp::image(open("images", path));
}

auto ce::assets::tileset(const std::string &path) const -> asset::tileset
{
	return asset::tileset(open("tilesets", path));
}

auto ce::assets::level(const std::string &path) const -> chirp::level
{
	return chirp::level(open("levels", path));
}
