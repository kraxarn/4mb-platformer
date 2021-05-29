#include "clf/clf.hpp"

auto clf::load(const std::filesystem::path &path) -> bool
{
	std::ifstream file(path, std::ios::out | std::ios::binary);
	if (!file)
	{
		std::cerr << "Failed to open: " << path.string() << std::endl;
		return false;
	}

	if (std::filesystem::file_size(path) != sizeof(struct clf_v2_data))
	{
		std::cerr << "Level data size mismatch (" << file.tellg()
			<< " and " << sizeof(struct clf_v2_data) << ")" << std::endl;
		return false;
	}

	file.read((char *) &data, sizeof(data));
	file.close();

	if (data.version != 2)
	{
		std::cerr << "Expected version 2, but found " << data.version
			<< ", loading may fail" << std::endl;
		return false;
	}

	return true;
}

auto clf::background() const -> std::string
{
	return std::string(data.background);
}

auto clf::is_boss() const -> bool
{
	return data.is_boss;
}

auto clf::map_size() const -> vec2
{
	return vec2(data.map_size[0], data.map_size[1]);
}

auto clf::tile_size() const -> int
{
	return data.tile_size;
}

auto clf::main_tileset() const -> std::string
{
	return std::string(data.main_tileset);
}

auto clf::item_tileset() const -> std::string
{
	return std::string(data.item_tileset);
}

auto clf::map() const -> std::array<std::array<unsigned char, 25>, 75>
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
