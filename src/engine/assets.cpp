#include "assets.hpp"

ce::assets::assets()
	: fs(cmrc::res::get_filesystem())
{
}

auto ce::assets::level(const std::string &path) -> ce::level
{
	return ce::level(fs.open(path));
}

auto ce::assets::all_levels() -> std::vector<ce::level>
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

auto ce::assets::music(const std::string &path) -> ce::music
{
	return ce::music(fs.open(path));
}
