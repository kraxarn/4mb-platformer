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
	dir = dir == direction::left
		? direction::right
		: direction::left;
}

auto ce::animated_sprite::width() const -> int
{
	return tileset.get_size();
}

auto ce::animated_sprite::height() const -> int
{
	return tileset.get_size();
}

auto ce::animated_sprite::size() const -> chirp::vector2i
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

auto ce::animated_sprite::get_dir() const -> direction
{
	return dir;
}

auto ce::animated_sprite::rect() const -> Rectangle
{
	return Rectangle{
		get_x(),
		get_y(),
		static_cast<float>(width()) * get_scale(),
		static_cast<float>(height()) * get_scale(),
	};
}

#ifndef NDEBUG
void ce::animated_sprite::debug_draw(const Color &color) const
{
	auto r = rect();
	DrawRectangleLines(static_cast<int>(r.x),
		static_cast<int>(r.y),
		static_cast<int>(r.width),
		static_cast<int>(r.height),
		color);
}
#endif
