#include "levelloader.hpp"

#include "engine/assets.hpp"
#include "engine/level.hpp"

#include <chirp/format.hpp>

auto level_loader::get(const ce::assets &assets, int index) -> ce::level *
{
	const auto level = assets.level(chirp::format("level{}", index));
	return new ce::level(level);
}

auto level_loader::is_valid(int index) -> bool
{
	return index >= 0 && index <= 9;
}
