#include "engine/level.hpp"
#include "engine/map.hpp"

#include "physics/tiles.hpp"

ce::level::level(const chirp::level &level)
	: chirp::level(level)
{
}

auto ce::level::get_total_gem_count() -> int
{
	if (gem_count < 0)
	{
		gem_count = 0;
		for (const auto &tile: tiles())
		{
			if (tile.value == static_cast<char>(tile::gem))
			{
				gem_count++;
			}
		}
	}

	return gem_count;
}

auto ce::level::get_spawn() const -> chirp::vector2i
{
	for (const auto &tile: tiles())
	{
		if (tile.value == static_cast<char>(tile::spawn))
		{
			return chirp::vector2(tile.x, tile.y).to<int>();
		}
	}

	return {};
}

auto ce::level::get_safe_spawn() const -> chirp::vector2f
{
	constexpr float player_tile_offset = 0.5F;
	const chirp::vector2f player_position = get_spawn().to<float>() * tile_size;
	return {
		player_position.x(),
		player_position.y() - tile_size * player_tile_offset,
	};
}
