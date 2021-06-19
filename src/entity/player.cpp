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
	update_collision(level);
	set_position(get_position() + velocity);

	// Draw sprite
	draw();
}

void player::update_collision(const ce::level &level)
{
	const auto &map = level.map();

	auto current_pos = get_position();
	current_pos.y += static_cast<float>(height()) * ce::tile_scale;

	auto target_pos = current_pos + velocity;

	auto target = (target_pos / ce::tile_size).to<int>();
	auto current = (current_pos / ce::tile_size).to<int>();

	auto new_tile_x = map.at(target.x).at(current.y);
	auto new_tile_y = map.at(current.x).at(target.y);

	if (new_tile_x >= 0)
	{
		velocity.x = 0.F;
	}
	if (new_tile_y >= 0)
	{
		velocity.y = 0.F;
	}

#ifndef NDEBUG
	debug_draw(Rectangle{
		static_cast<float>(target.x) * ce::tile_size,
		static_cast<float>(target.y) * ce::tile_size,
		ce::tile_size,
		ce::tile_size,
	}, BLUE);
#endif
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
	debug_draw(rect(), GREEN);
}

void player::debug_draw(const Rectangle &rect, const Color &color)
{
	DrawRectangleLines(static_cast<int>(rect.x),
		static_cast<int>(rect.y),
		static_cast<int>(rect.width),
		static_cast<int>(rect.height),
		color);
}
#endif
