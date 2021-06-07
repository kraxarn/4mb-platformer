#include "movable.hpp"

auto ce::movable::get_x() const -> float
{
	return pos.x;
}

void ce::movable::set_x(float value)
{
	pos.x = value;
}

auto ce::movable::get_y() const -> float
{
	return pos.y;
}

void ce::movable::set_y(float value)
{
	pos.y = value;
}

void ce::movable::set_pos(const ce::vector2f &new_pos)
{
	pos = new_pos;
}

auto ce::movable::get_pos() const -> ce::vector2f
{
	return pos;
}

void ce::movable::move(float x_offset, float y_offset)
{
	pos.x += x_offset;
	pos.y += y_offset;
}
