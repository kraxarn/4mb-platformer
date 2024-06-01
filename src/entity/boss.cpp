#include "boss.hpp"

#include "engine/map.hpp"

#include <chirp/colors.hpp>
#include <chirp/random.hpp>

entity::boss::boss(const chirp::assets &assets, const chirp::vector2f &player_pos, const float scale)
	: animated_sprite(assets.tileset("enemy")),
	player_pos(player_pos),
	snd_boss(assets.sound("boss"))
{
	set_scale(scale);
}

void entity::boss::update(const bool is_paused, const float delta)
{
	if (health <= 0)
	{
		return;
	}

	if (!is_paused)
	{
		animated_sprite::update(delta);

		// Movement
		auto dir = get_player_dirs();
		auto dist = get_player_dist();
		auto speed = get_speed();
		const auto shape = get_shape();

		auto x = dist.x() < shape.width()
			? 0.F : eq(dir, chirp::direction::left)
				? -speed : speed;
		auto y = lock_y || dist.y() < shape.height()
			? 0.F : eq(dir, chirp::direction::up)
				? -speed : speed;

		set_position(get_position() + chirp::vector2f(x, y));

		// Flip if needed
		if (x < 0 && get_direction() == chirp::direction::right
			|| x > 0 && get_direction() == chirp::direction::left)
		{
			flip_horizontal();
		}
	}

	// Draw sprite
	draw();
#ifndef NDEBUG
	debug_draw(chirp::colors::blue());
#endif
}

auto entity::boss::get_player_dirs() const -> chirp::direction
{
	const auto &pos = get_position();

	return static_cast<chirp::direction>(static_cast<unsigned short>(player_pos.x() > pos.x()
		? chirp::direction::right : chirp::direction::left)
		| static_cast<unsigned char>(player_pos.y() > pos.y()
			? chirp::direction::down : chirp::direction::up));
}

auto entity::boss::eq(const chirp::direction &dir1, const chirp::direction &dir2) -> bool
{
	return (static_cast<unsigned short>(dir1) & static_cast<unsigned short>(dir2))
		!= static_cast<unsigned short>(chirp::direction::none);
}

auto entity::boss::get_player_dist() const -> chirp::vector2f
{
	const auto &pos = get_position();

	return {
		std::abs(pos.x() - player_pos.x()),
		std::abs(pos.y() + player_pos.y()),
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
	snd_boss->play();
	health--;

	auto is_dead = health <= 0;
	set_position(is_dead ? chirp::vector2f() : get_random_pos());
	return is_dead;
}

auto entity::boss::get_random_pos() const -> chirp::vector2f
{
	return {
		player_pos.x()
			+ static_cast<float>(chirp::random::get(min_random_move, max_random_move))
			* (chirp::random::get(0, 1) == 0 ? -1.F : 1.F),
		get_position().y(),
	};
}

auto entity::boss::get_speed() const -> float
{
	auto diff = max_speed - min_speed;
	auto step = diff / static_cast<float>(initial_health);
	auto speed = max_speed - static_cast<float>(health) * step;

	return lock_y && player_pos.y() + ce::tile_size < get_position().y()
		? -speed / 2.F
		: speed;
}
