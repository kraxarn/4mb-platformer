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
