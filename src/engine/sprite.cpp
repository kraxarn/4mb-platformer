#include "sprite.hpp"

ce::sprite::sprite(const ce::tileset &tileset)
	: tileset(tileset)
{
}

void ce::sprite::draw()
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

	tileset.draw(frame, rotation, scale);
}

void ce::sprite::set_pos(float x, float y)
{
	tileset.set_pos(x, y);
}

void ce::sprite::move(float x, float y)
{
	tileset.move(x, y);
}

void ce::sprite::set_scale(float value)
{
	scale = value;
}

void ce::sprite::rotate(float value)
{
	rotation += value;
}
auto ce::sprite::x() const -> float
{
	return tileset.x();
}

auto ce::sprite::y() const -> float
{
	return tileset.y();
}
