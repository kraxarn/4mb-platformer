#include "entity/player.hpp"

entity::player::player(const ce::assets &assets, entity::hud &hud, float scale)
	: ce::animated_sprite(assets.tileset("player.png")),
	snd_jump(assets.sound("jump.wav")),
	snd_fall(assets.sound("fall.wav")),
	hud(hud)
{
	// Sprite
	set_scale(scale);
}

void entity::player::update(const ce::input &input, ce::level &level)
{
	// Right
	if (input.is_down(ce::key::right))
	{
		velocity.x += move_acceleration;
		if (velocity.x > speed_limit)
		{
			velocity.x = speed_limit;
		}
	}
	else if (velocity.x > 0 && is_grounded())
	{
		velocity.x += move_deceleration;
		if (velocity.x < 0)
		{
			velocity.x = 0;
		}
	}

	// Left
	if (input.is_down(ce::key::left))
	{
		velocity.x -= move_acceleration;
		if (velocity.x < -speed_limit)
		{
			velocity.x = -speed_limit;
		}
	}
	else if (velocity.x < 0 && is_grounded())
	{
		velocity.x -= move_deceleration;
		if (velocity.x > 0)
		{
			velocity.x = 0;
		}
	}

	// Jump
	if (input.is_down(ce::key::jump) && is_grounded())
	{
		snd_jump.play();
		ce::animated_sprite::pause();
		set_frame(1);
		velocity.y = jump_force;
	}
	else
	{
		velocity.y += gravity;
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
	if (!hud.is_dead())
	{
		update_collision(level);
	}
	set_position(get_position() + velocity);

	if (velocity.x == 0)
	{
		ce::animated_sprite::pause();
		set_frame(0);
	}
	else if (is_grounded())
	{
		ce::animated_sprite::resume();
	}

	// Player died or fell out of the stage
	if (get_y() > kill_limit)
	{
		if (!hud.is_dead())
		{
			snd_fall.play();
		}
		velocity = ce::vector2f();
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

auto entity::player::get_velocity() const -> const ce::vector2f &
{
	return velocity;
}

auto entity::player::is_grounded() const -> bool
{
	return velocity.y == 0;
}

auto entity::player::get_player_dir() const -> direction
{
	return velocity.x < 0
		? direction::left
		: velocity.x > 0
			? direction::right
			: get_dir();
}
