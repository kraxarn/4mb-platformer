#include "entity/player.hpp"

entity::player::player(const ce::assets &assets, float scale)
	: ce::animated_sprite(assets.tileset("player.png")),
	snd_jump(assets.sound("jump.wav"))
{
	// Sprite
	set_scale(scale);
}

void entity::player::update(const ce::input &input, const ce::level &level)
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
		velocity.y = jump_force;
	}
	else
	{
		velocity.y += gravity;
	}

#ifndef NDEBUG
	// update_collision draws some stuff in debug
	draw();
#endif

	// Update position
	update_collision(level);
	set_position(get_position() + velocity);

#ifdef NDEBUG
	// Draw sprite
	draw();
#endif
}

void entity::player::update_collision(const ce::level &level)
{
	auto colliding = phys::collision::will_collide(rect(), level, velocity);

#ifndef NDEBUG
	debug_draw(rect(), colliding ? GREEN : RED);
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

#ifndef NDEBUG
void entity::player::debug_draw() const
{
	debug_draw(rect(), GREEN);
}

void entity::player::debug_draw(const Rectangle &rect, const Color &color)
{
	DrawRectangleLines(static_cast<int>(rect.x),
		static_cast<int>(rect.y),
		static_cast<int>(rect.width),
		static_cast<int>(rect.height),
		color);
}

auto entity::player::get_collides() const -> const ce::vector2<bool> &
{
	return collides;
}
#endif
