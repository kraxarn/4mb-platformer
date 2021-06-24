#include "boss.hpp"

entity::boss::boss(const ce::assets &assets, const ce::movable &player, float scale)
	: ce::animated_sprite(assets.tileset("enemy.png")),
	player(player),
	snd_boss(assets.sound("boss.wav"))
{
	set_scale(scale);
}

void entity::boss::update()
{
	if (health <= 0)
	{
		return;
	}

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

auto entity::boss::hurt() -> bool
{
	snd_boss.play();
	health--;

	auto is_dead = health <= 0;
	set_position(is_dead ? ce::vector2f() : get_random_pos());
	return is_dead;
}

auto entity::boss::get_random_pos() const -> ce::vector2f
{
	return {
		player.get_x()
			+ static_cast<float>(GetRandomValue(min_random_move, max_random_move))
				* (GetRandomValue(0, 1) == 0 ? -1.F : 1.F),
		get_y(),
	};
}
