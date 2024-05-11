#include "engine/level.hpp"

#include "physics/tiles.hpp"

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

auto ce::level::get_spawn() const -> chirp::vector2i
{
	chirp::vector2i vec;

	ce::iterate_map<char>(map(), [&vec](auto x, auto y, char value) -> bool
	{
		if (value == static_cast<char>(tile::spawn))
		{
			vec = chirp::vector2<std::size_t>(x, y).to<int>();
			return true;
		}
		return false;
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
