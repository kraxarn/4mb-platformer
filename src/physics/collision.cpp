#include "physics/collision.hpp"

auto phys::collision::get_tile_type(char value) -> tile_type
{
	return value == static_cast<char>(tile::none)
		? tile_type::empty
		: value < static_cast<char>(tile::spawn)
			? tile_type::tile
			: value <= static_cast<char>(tile::spike) // Last valid tile
				? tile_type::item
				: tile_type::invalid;
}

auto phys::collision::will_collide(const Rectangle &player_rect,
	const ce::level &level, ce::vector2f &velocity) -> bool
{
	auto collides = false;
	const auto &map = level.map();
	auto rect = player_rect;
	ce::vector2f player_position(rect.x, rect.y);
	auto player_tile = (player_position / ce::tile_size).to<int>();

	auto rect_x = rect;
	rect_x.x += velocity.x;
	if (will_collide(level, player_tile, rect_x))
	{
		velocity.x = 0.F;
		collides = true;
	}

	auto rect_y = rect;
	rect_y.y += velocity.y;
	if (will_collide(level, player_tile, rect_y))
	{
		velocity.y = 0.F;
		collides = true;
	}

	return collides;
}

auto phys::collision::will_collide(const ce::level &level,
	const ce::vector2i &tile, const Rectangle &rect) -> bool
{
	const auto &map = level.map();
	tile_type tile_type;
	int x;
	int y;

	Rectangle target{};
	target.width = ce::tile_size;
	target.height = ce::tile_size;

	for (x = tile.x - offset; x < tile.x + offset; x++)
	{
		if (x < 0 || x >= map.size())
		{
			continue;
		}

		for (y = tile.y - offset; y < tile.y + offset; y++)
		{
			if (y < 0 || y >= map.at(x).size())
			{
				continue;
			}

			tile_type = get_tile_type(map.at(x).at(y));
			if (tile_type != tile_type::tile)
			{
				continue;
			}

			target.x = static_cast<float>(x) * ce::tile_size;
			target.y = static_cast<float>(y) * ce::tile_size;

			if (CheckCollisionRecs(rect, target))
			{
				return true;
			}
		}
	}

	return false;
}
