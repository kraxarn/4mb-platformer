#include "physics/collision.hpp"

auto phys::collision::is_tile(char value) -> bool
{
	return value > static_cast<char>(tile::none)
		&& value < static_cast<char>(tile::spawn);
}

auto phys::collision::can_collide(const ce::level &level, int x, int y) -> bool
{
	const auto &map = level.map();
	const auto &value = map.at(x).at(y);

	// Only tiles require collision
	if (!is_tile(value))
	{
		return false;
	}

	// If surrounded, collision isn't required
	return !(y > 0 && is_tile(map.at(x).at(y - 1))                  // above
		&& y < map.at(x).size() - 1 && is_tile(map.at(x).at(y + 1)) // below
		&& x > 0 && is_tile(map.at(x - 1).at(y))                    // left
		&& x < map.size() - 1 && is_tile(map.at(x + 1).at(y)));     // right
}

auto phys::collision::will_collide(const Rectangle &player_rect,
	const ce::level &level, ce::vector2f &velocity) -> bool
{
	const auto &map = level.map();
	auto rect = player_rect;
	ce::vector2f player_position(rect.x, rect.y);
	auto player_tile = (player_position / ce::tile_size).to<int>();

	rect.x += velocity.x;
	if (will_collide(level, player_tile, rect))
	{
		velocity.x = 0.F;
		return true;
	}

	rect.y += velocity.y;
	if (will_collide(level, player_tile, rect))
	{
		velocity.y = 0.F;
		return true;
	}

	return false;
}

auto phys::collision::will_collide(const ce::level &level,
	const ce::vector2i &tile, const Rectangle &rect) -> bool
{
	const auto &map = level.map();
	int x;
	int y;

	Rectangle target{};
	target.width = ce::tile_size;
	target.height = ce::tile_size;

	for (x = tile.x - 1; x < tile.x + 1; x++)
	{
		for (y = tile.y - 1; y < tile.y + 1; y++)
		{
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
