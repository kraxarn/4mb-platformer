#include "boss.hpp"

entity::boss::boss(const ce::assets &assets, const ce::movable &player, float scale)
	: ce::animated_sprite(assets.tileset("enemy.png")),
	player(player)
{
	set_scale(scale);
}

void entity::boss::update()
{
	// Flip if needed
	auto dir = get_player_dirs();
	if (!eq(dir, get_dir()))
	{
		flip();
	}

	move(eq(dir, direction::left) ? -move_speed : move_speed,
		eq(dir, direction::up) ? -move_speed : move_speed);

	draw();
}

auto entity::boss::get_player_dirs() const -> direction
{
	return static_cast<direction>(static_cast<unsigned short>(player.get_x() > get_x()
		? direction::right : direction::left)
		| static_cast<unsigned char>(player.get_y() > get_y()
			? direction::down : direction::up));
}

auto entity::boss::eq(const direction &dir1, const direction &dir2) -> bool
{
	return (static_cast<unsigned short>(dir1) & static_cast<unsigned short>(dir2))
		!= static_cast<unsigned short>(direction::none);
}
