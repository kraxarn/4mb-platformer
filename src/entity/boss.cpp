#include "boss.hpp"
#include "engine/map.hpp"

entity::boss::boss(const ce::assets &assets, const ce::movable &player, float scale)
	: ce::animated_sprite(assets.tileset("enemy")),
	player(player),
	snd_boss(assets.sound("boss"))
{
	set_scale(scale);
}

void entity::boss::update(bool is_paused)
{
	if (health <= 0)
	{
		return;
	}

	if (!is_paused)
	{
		// Movement
		auto dir = get_player_dirs();
		auto dist = get_player_dist();
		auto speed = get_speed();

		auto x = dist.x() < static_cast<float>(width())
			? 0.F : eq(dir, direction::left)
				? -speed : speed;
		auto y = lock_y || dist.y() < static_cast<float>(height())
			? 0.F : eq(dir, direction::up)
				? -speed : speed;
		move(x, y);

		// Flip if needed
		if (x < 0 && get_dir() == direction::right
			|| x > 0 && get_dir() == direction::left)
		{
			flip();
		}
	}

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

auto entity::boss::get_player_dist() const -> chirp::vector2f
{
	return {
		std::abs(get_x() - player.get_x()),
		std::abs(get_y() + player.get_y()),
	};
}

auto entity::boss::is_final(const chirp::level *level) -> bool
{
	return level->type() == "final_boss";
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
	set_position(is_dead ? chirp::vector2f() : get_random_pos());
	return is_dead;
}

auto entity::boss::get_random_pos() const -> chirp::vector2f
{
	return {
		player.get_x()
			+ static_cast<float>(GetRandomValue(min_random_move, max_random_move))
				* (GetRandomValue(0, 1) == 0 ? -1.F : 1.F),
		get_y(),
	};
}

auto entity::boss::get_speed() const -> float
{
	auto diff = max_speed - min_speed;
	auto step = diff / static_cast<float>(initial_health);
	auto speed = max_speed - static_cast<float>(health) * step;

	return lock_y && player.get_y() + ce::tile_size < get_y()
		? -speed / 2.F
		: speed;
}
