#include "assets.hpp"

ce::assets::assets()
	: fs(cmrc::res::get_filesystem())
{
}

auto ce::assets::open(const std::string &folder,
	const std::string &filename) const -> cmrc::file
{
	std::stringstream stream;
	stream << folder << "/" << filename;
	return fs.open(stream.str());
}

auto ce::assets::level(const std::string &path) const -> ce::level
{
	return ce::level(fs.open(path));
}

auto ce::assets::all_levels() const -> std::vector<ce::level>
{
	std::vector<ce::level> levels;
	for (const auto &file : fs.iterate_directory("level"))
	{
		std::stringstream path;
		path << "level/" << file.filename();
		levels.emplace_back(level(path.str()));
	}
	return levels;
}

auto ce::assets::music(const std::string &path) const -> ce::music
{
	return ce::music(fs.open(path));
}

auto ce::assets::font(const std::string &path, int font_size) const -> ce::font
{
	return ce::font(fs.open(path), font_size);
}

auto ce::assets::image(const std::string &path) const -> ce::image
{
	return ce::image(open("image", path));
}
