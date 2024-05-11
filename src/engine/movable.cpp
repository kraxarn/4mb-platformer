#include "movable.hpp"

auto ce::movable::get_x() const -> float
{
	return pos.x();
}

void ce::movable::set_x(float value)
{
	pos = {value, pos.y()};
}

auto ce::movable::get_y() const -> float
{
	return pos.y();
}

void ce::movable::set_y(float value)
{
	pos = {pos.x(), value};
}

void ce::movable::set_position(const chirp::vector2f &new_pos)
{
	pos = new_pos;
}

auto ce::movable::get_position() const -> chirp::vector2f
{
	return pos;
}

void ce::movable::move(float x_offset, float y_offset)
{
	pos += chirp::vector2f(x_offset, y_offset);
}
