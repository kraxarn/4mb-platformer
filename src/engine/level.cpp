#include "engine/level.hpp"

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
