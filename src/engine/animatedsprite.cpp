#include "animatedsprite.hpp"

ce::animated_sprite::animated_sprite(const asset::tileset &tileset)
	: tileset(tileset)
{
}

void ce::animated_sprite::draw()
{
	if (running)
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

void ce::animated_sprite::flip()
{
	tileset.flip_horizontal();
}

auto ce::animated_sprite::width() const -> int
{
	return tileset.get_size();
}

auto ce::animated_sprite::height() const -> int
{
	return tileset.get_size();
}

auto ce::animated_sprite::size() const -> ce::vector2i
{
	return {
		width(),
		height(),
	};
}

void ce::animated_sprite::set_frame(int index)
{
	frame = index;
}

void ce::animated_sprite::pause()
{
	running = false;
}

void ce::animated_sprite::resume()
{
	running = true;
}
