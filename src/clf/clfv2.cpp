#include "clfv2.hpp"

auto clf_v2::parse(const std::filesystem::path &path) -> clf
{
	std::ifstream file(path, std::ios::out | std::ios::binary);
	if (!file)
	{
		std::cerr << "Failed to open: " << path.string() << std::endl;
	}

	if (std::filesystem::file_size(path) != sizeof(struct clf_v2_data))
	{
		std::cerr << "Level data size mismatch (" << file.tellg()
			<< " and " << sizeof(struct clf_v2_data) << ")" << std::endl;
	}

	struct clf_v2_data data;
	file.read((char *) &data, sizeof(data));
	file.close();

	if (data.version != 2)
	{
		std::cerr << "Expected version 2, but found " << data.version
			<< ", loading may fail" << std::endl;
	}

	clf level;
	level.version = 3;
	level.background = std::string(data.background);
	level.level_type = data.is_boss
		? e::level_type::boss
		: e::level_type::normal;
	level.map_size = vec2(data.map_size[0], data.map_size[1]);
	level.tile_size = data.tile_size;
	level.main_tileset = std::string(data.main_tileset);
	level.item_tileset = std::string(data.item_tileset);

	level.map.reserve(75);
	for (auto &x : data.map)
	{
		std::vector<unsigned char> row;
		row.reserve(25);
		for (int y : x)
		{
			row.push_back(static_cast<unsigned char>(y));
		}
		level.map.push_back(row);
	}

	return level;
}
