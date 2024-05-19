#include "entity/player.hpp"

entity::player::player(const chirp::assets &assets, entity::hud &hud, float scale)
	: ce::animated_sprite(assets.tileset("player")),
	snd_jump(assets.sound("jump")),
	snd_fall(assets.sound("fall")),
	hud(hud)
{
	// Sprite
	set_scale(scale);
}

void entity::player::update(const keymap &keymap,
	ce::level &level, bool is_paused)
{
	if (!is_paused)
	{
		auto speed_limit_x = speed_limit * hud.get_player_speed_modifier();

		// Right
		if (keymap.is_down("right"))
		{
			velocity += chirp::vector2f(move_acceleration, 0);
			if (velocity.x() > speed_limit_x)
			{
				velocity = {speed_limit_x, velocity.y()};
			}
		}
		else if (velocity.x() > 0 && is_grounded())
		{
			velocity += chirp::vector2f(move_deceleration, 0);
			if (velocity.x() < 0)
			{
				velocity = {0, velocity.y()};
			}
		}

		// Left
		if (keymap.is_down("left"))
		{
			velocity -= chirp::vector2f(move_acceleration, 0);
			if (velocity.x() < -speed_limit_x)
			{
				velocity = {-speed_limit_x, velocity.y()};
			}
		}
		else if (velocity.x() < 0 && is_grounded())
		{
			velocity -= chirp::vector2f(move_deceleration, 0);
			if (velocity.x() > 0)
			{
				velocity = {0, velocity.y()};
			}
		}

		// Jump
		if (keymap.is_down("jump") && is_grounded())
		{
			snd_jump->play();
			ce::animated_sprite::pause();
			set_frame(1);
			velocity = {velocity.x(), jump_force};
		}
		else
		{
			velocity += chirp::vector2f(0, gravity);
		}
	}

	// Flip image if needed
	const auto new_dir = get_player_dir();
	if (get_dir() != new_dir)
	{
		ce::animated_sprite::flip();
	}

#ifndef NDEBUG
	// update_collision draws some stuff in debug
	draw();
#endif

	// Update position
	if (!is_paused)
	{
		if (!hud.is_dead())
		{
			update_collision(level);
		}
		set_position(get_position() + velocity);

		if (velocity.x() == 0)
		{
			ce::animated_sprite::pause();
			set_frame(0);
		}
		else if (is_grounded())
		{
			ce::animated_sprite::resume();
		}
	}

	// Player died or fell out of the stage
	if (get_y() > kill_limit)
	{
		if (!hud.is_dead())
		{
			snd_fall->play();
		}
		velocity = chirp::vector2f();
		set_position(level.get_safe_spawn());
		hud.respawn();
	}

#ifdef NDEBUG
	// Draw sprite
	draw();
#endif
}

void entity::player::update_collision(ce::level &level)
{
	auto colliding = phys::collision::update(rect(), level, velocity, hud);

#ifndef NDEBUG
	debug_draw(colliding == tile_type::tile ? GREEN : RED);
#endif
}

auto entity::player::get_velocity() const -> const chirp::vector2f &
{
	return velocity;
}

auto entity::player::is_grounded() const -> bool
{
	return velocity.y() == 0;
}

auto entity::player::get_player_dir() const -> chirp::direction
{
	if (velocity.x() < 0)
	{
		return chirp::direction::left;
	}

	if (velocity.x() > 0)
	{
		return chirp::direction::right;
	}

	return get_dir();
}
