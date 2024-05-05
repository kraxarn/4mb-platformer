#include "levelloader.hpp"

#include "asset/level.hpp"
#include "engine/assets.hpp"

auto level_loader::get(const ce::assets &assets, int index) -> ce::level *
{
	const auto level = assets.level(ce::fmt::format("level{}.clf", index));
	return new asset::level(level);
}

auto level_loader::is_valid(int index) -> bool
{
	return index >= 0 && index <= 9;
}
