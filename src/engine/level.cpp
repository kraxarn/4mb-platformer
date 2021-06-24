#include "engine/level.hpp"

ce::level::level(ce::map<char> map_data)
	: map_data(map_data)
{
}

auto ce::level::map() const -> const ce::map<char> &
{
	return map_data;
}

auto ce::level::get_total_gem_count() -> int
{
	if (gem_count < 0)
	{
		gem_count = 0;
		iterate_map_all<char>(map(), [this](int /*x*/, int /*y*/, char tile)
		{
			if (tile == static_cast<char>(tile::gem))
			{
				gem_count++;
			}
		});
	}

	return gem_count;
}

void ce::level::set_tile(int x, int y, char value)
{
	map_data.at(x).at(y) = value;
}
