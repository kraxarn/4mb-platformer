#include "animatedsprite.hpp"

ce::animated_sprite::animated_sprite(const ce::tileset &tileset)
	: tileset(tileset),
	movable()
{
}

void ce::animated_sprite::draw()
{
	current++;
	if (current >= time)
	{
		current = 0;
		frame++;
		if (frame >= tileset.get_size())
		{
			frame = 0;
		}
	}

	tileset.draw(get_x(), get_y(), frame, rotation, scale);
}

auto ce::animated_sprite::get_scale() const -> float
{
	return scale;
}

void ce::animated_sprite::set_scale(float value)
{
	scale = value;
}

void ce::animated_sprite::rotate(float value)
{
	rotation += value;
}

auto ce::animated_sprite::width() const -> int
{
	return tileset.get_size();
}

auto ce::animated_sprite::height() const -> int
{
	return tileset.get_size();
}
