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
		velocity.x += move_force;
	}

	// Left
	if (input.is_down(ce::key::left))
	{
		velocity.x -= move_force;
	}

	// Jump
	if (input.is_pressed(ce::key::jump))
	{
		velocity.y += jump_force;
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

auto player::rect() const -> Rectangle
{
	return ce::rect::get(*this);
}

#ifndef NDEBUG
void player::debug_draw() const
{
	DrawRectangleRec(rect(), GREEN);
}
#endif
