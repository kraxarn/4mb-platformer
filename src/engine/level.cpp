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
		iterate([this](const chirp::map_tile &tile) -> bool
		{
			if (tile.value == static_cast<char>(tile::gem))
			{
				gem_count++;
			}
			return true;
		});
	}

	return gem_count;
}

auto ce::level::get_spawn() const -> chirp::vector2i
{
	chirp::vector2i vec;

	iterate([&vec](const chirp::map_tile &tile) -> bool
	{
		if (tile.value == static_cast<char>(tile::spawn))
		{
			vec = chirp::vector2<std::size_t>(tile.x, tile.y).to<int>();
			return false;
		}
		return true;
	});

	return vec;
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
