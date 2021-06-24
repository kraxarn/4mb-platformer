#include "boss.hpp"

entity::boss::boss(const ce::assets &assets, const ce::movable &player, float scale)
	: ce::animated_sprite(assets.tileset("enemy.png")),
	player(player)
{
	set_scale(scale);
}

void entity::boss::update()
{
	auto new_dir = get_player_dir();
	if (get_dir() != new_dir)
	{
		flip();
	}

	draw();
}

auto entity::boss::get_player_dir() const -> direction
{
	return player.get_x() > get_x()
		? direction::right
		: direction::left;
}
