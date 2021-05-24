#include "clfv3.hpp"

auto clf_v3::save(const clf &level, const std::filesystem::path &path) -> bool
{
	std::stringstream stream;

	stream
		<< "version=" << level.version << '\n'
		<< "name=" << level.name << '\n'
		<< "music=" << level.music << '\n'
		<< "main_tileset=" << level.main_tileset << '\n'
		<< "item_tileset=" << level.item_tileset << '\n'
		<< "tile_size=" << level.tile_size << '\n'
		<< "background=" << level.background << '\n'
		<< "level_type=" << level.level_type_string() << '\n'
		<< "map_size=" << level.map_size.to_string() << '\n'
		<< "map=" << '\n';

	for (auto &x : level.map)
	{
		for (int y : x)
		{
			stream << y << ',';
		}
		stream << '\n';
	}

	std::ofstream file(path);
	file << stream.str();
	file.close();

	return true;
}
