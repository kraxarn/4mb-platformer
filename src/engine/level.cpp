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

auto ce::level::get_spawn() const -> ce::vector2i
{
	ce::vector2i vec;

	ce::iterate_map<char>(map(), [&vec](auto x, auto y, char value) -> bool
	{
		if (value == static_cast<char>(tile::spawn))
		{
			vec = ce::vector2<std::size_t>(x, y).to<int>();
			return true;
		}
		return false;
	});

	return vec;
}

auto ce::level::get_safe_spawn() const -> ce::vector2f
{
	constexpr float player_tile_offset = 0.5F;
	ce::vector2f player_position = get_spawn().to<float>() * ce::tile_size;
	player_position.y = player_position.y - ce::tile_size * player_tile_offset;
	return player_position;
}
