#include "player.hpp"

player::player(const ce::assets &assets, float scale)
	: ce::animated_sprite(assets.tileset("player.png"))
{
	// Sprite
	set_scale(scale);
}

void player::update(const ce::input &input, const ce::level &level)
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
		velocity.y -= jump_acceleration;
	}
	else
	{
		velocity.y -= jump_deceleration;
	}

	// Update position
	set_position(get_position() + velocity);

	// Draw sprite
	draw();
}

auto player::get_velocity() const -> const ce::vector2f &
{
	return velocity;
}

auto player::is_grounded() const -> bool
{
	return velocity.y == 0;
}

auto player::rect() const -> Rectangle
{
	// Sprite position is based off the center of the sprite
	// Rectangle position is based off the top-left corner

	const auto w = static_cast<float>(width());
	const auto h = static_cast<float>(height());

	return Rectangle{
		get_x() - (w / 2.F),
		get_y() - (h / 2.F),
		w * get_scale(),
		h * get_scale(),
	};
}

#ifndef NDEBUG
void player::debug_draw() const
{
	const auto sprite_rect = rect();
	DrawRectangleLines(static_cast<int>(sprite_rect.x),
		static_cast<int>(sprite_rect.y),
		static_cast<int>(sprite_rect.width),
		static_cast<int>(sprite_rect.height),
		GREEN);
}
#endif
