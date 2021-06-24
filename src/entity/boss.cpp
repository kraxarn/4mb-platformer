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

	// Movement
	auto dist = get_player_dist();
	auto x = dist.x < static_cast<float>(width())
		? 0.F : eq(dir, direction::left)
			? -move_speed : move_speed;
	auto y = lock_y || dist.y < static_cast<float>(height())
		? 0.F : eq(dir, direction::up)
			? -move_speed : move_speed;
	move(x, y);

	// Draw sprite
	draw();
#ifndef NDEBUG
	debug_draw(BLUE);
#endif
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

auto entity::boss::get_player_dist() const -> ce::vector2f
{
	return {
		std::abs(get_x() - player.get_x()),
		std::abs(get_y() + player.get_y()),
	};
}

auto entity::boss::is_final(const ce::level *level) -> bool
{
	return dynamic_cast<const level10 *>(level) != nullptr;
}

void entity::boss::set_lock_y(bool value)
{
	lock_y = value;
}
