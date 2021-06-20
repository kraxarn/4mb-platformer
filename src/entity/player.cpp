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
		velocity.y = jump_force;
	}
	else
	{
		velocity.y -= gravity;
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

void player::update_collision(const ce::level &level)
{
	const auto &map = level.map();
	const auto w = static_cast<float>(width()) * ce::tile_scale;
	const auto h = static_cast<float>(height()) * ce::tile_scale;

	auto current_pos = get_position();
	current_pos.y += h;

	auto target_pos = current_pos;
	target_pos.x += w * (velocity.x > 0.F ? 1.F : velocity.x < 0.F ? 0.F : 0.5F);

	auto target = (target_pos / ce::tile_size).to<int>();
	auto current = (current_pos / ce::tile_size).to<int>();

	auto new_tile_x = map.at(target.x).at(current.y);
	auto new_tile_y = map.at(current.x).at(target.y);

	if (phys::collision::is_tile(new_tile_x))
	{
		velocity.x = 0.F;
	}
	if (phys::collision::is_tile(new_tile_y))
	{
		velocity.y = 0.F;
	}

#ifndef NDEBUG
	debug_draw(Rectangle{
		static_cast<float>(target.x) * ce::tile_size,
		static_cast<float>(target.y) * ce::tile_size,
		ce::tile_size,
		ce::tile_size,
	}, RED);

	DrawText(std::to_string(new_tile_x).c_str(),
		target.x * static_cast<int>(ce::tile_size) + 6,
		current.y * static_cast<int>(ce::tile_size) + 6,
		12.F, RED);

	auto target_vec = target_pos.to<int>();
	DrawCircle(target_vec.x, target_vec.y,
		3.F, RED);
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
	return Rectangle{
		get_x(),
		get_y(),
		static_cast<float>(width()) * get_scale(),
		static_cast<float>(height()) * get_scale(),
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
