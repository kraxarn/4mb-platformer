#include "movable.hpp"

auto ce::movable::get_x() const -> float
{
	return x;
}

void ce::movable::set_x(float value)
{
	x = value;
}

auto ce::movable::get_y() const -> float
{
	return y;
}

void ce::movable::set_y(float value)
{
	y = value;
}

void ce::movable::move(float x_offset, float y_offset)
{
	x += x_offset;
	y += y_offset;
}
