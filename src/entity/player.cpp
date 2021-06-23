#include "entity/player.hpp"

entity::player::player(const ce::assets &assets, entity::hud &hud, float scale)
	: ce::animated_sprite(assets.tileset("player.png")),
	snd_jump(assets.sound("jump.wav")),
	hud(hud)
{
	// Sprite
	set_scale(scale);

	// By default, the sprite is facing left
	dir = direction::left;
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
	if (input.is_pressed(ce::key::jump) && is_grounded())
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
	const auto new_dir = get_dir();
	if (dir != new_dir)
	{
		dir = new_dir;
		ce::animated_sprite::flip();
	}

#ifndef NDEBUG
	// update_collision draws some stuff in debug
	draw();
#endif

	// Update position
	update_collision(level);
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

#ifdef NDEBUG
	// Draw sprite
	draw();
#endif
}

void entity::player::update_collision(ce::level &level)
{
	auto colliding = phys::collision::update(rect(), level, velocity, hud);

#ifndef NDEBUG
	debug_draw(rect(), colliding == tile_type::tile ? GREEN : RED);
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

auto entity::player::rect() const -> Rectangle
{
	return Rectangle{
		get_x(),
		get_y(),
		static_cast<float>(width()) * get_scale(),
		static_cast<float>(height()) * get_scale(),
	};
}

auto entity::player::get_dir() const -> direction
{
	return velocity.x < 0
		? direction::left
		: velocity.x > 0
			? direction::right
			: dir;
}

#ifndef NDEBUG
void entity::player::debug_draw(const Rectangle &rect, const Color &color)
{
	DrawRectangleLines(static_cast<int>(rect.x),
		static_cast<int>(rect.y),
		static_cast<int>(rect.width),
		static_cast<int>(rect.height),
		color);
}
#endif
