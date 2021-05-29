#include "engine/level.hpp"

ce::level::level(const cmrc::file &file)
{
	if (file.size() != sizeof(struct clf_v2_data))
	{
		std::cerr << "Level data size mismatch (" << file.size()
			<< " and " << sizeof(struct clf_v2_data) << ")" << std::endl;
		return;
	}
	data = *((struct clf_v2_data *) file.cbegin());

	if (data.version != 2)
	{
		std::cerr << "Expected version 2, but found " << data.version
			<< ", loading may fail" << std::endl;
		return;
	}
}

auto ce::level::background() const -> std::string
{
	return std::string(data.background);
}

auto ce::level::is_boss() const -> bool
{
	return data.is_boss;
}

auto ce::level::map_size() const -> vec2
{
	return vec2(data.map_size[0], data.map_size[1]);
}

auto ce::level::tile_size() const -> int
{
	return data.tile_size;
}

auto ce::level::main_tileset() const -> std::string
{
	return std::string(data.main_tileset);
}

auto ce::level::item_tileset() const -> std::string
{
	return std::string(data.item_tileset);
}

auto ce::level::map() const -> std::array<std::array<unsigned char, 25>, 75>
{
	std::array<std::array<unsigned char, 25>, 75> map = {0};

	for (auto x = 0; x < 75; x++)
	{
		for (auto y = 0; y < 25; y++)
		{
			map.at(x).at(y) = data.map[x][y];
		}
	}

	return map;
}
