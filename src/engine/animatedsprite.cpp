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

void ce::animated_sprite::set_scale(float value)
{
	scale = value;
}

void ce::animated_sprite::rotate(float value)
{
	rotation += value;
}
