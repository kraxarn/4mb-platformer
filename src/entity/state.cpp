#include "state.hpp"

auto entity::state::get_coins() const -> int
{
	return coins;
}

void entity::state::add_coins(int amount)
{
	coins += amount;
}

auto entity::state::get_gems() const -> int
{
	return gems;
}

void entity::state::set_gems(int value)
{
	gems = value;
}

void entity::state::add_gems(int amount)
{
	gems += amount;
}
