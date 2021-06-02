#include "tileset.hpp"

ce::tileset::tileset(const cmrc::file &file)
	: image(file),
	texture(image)
{
	size = texture.get_height();
	count = texture.get_width() / size;
}

void ce::tileset::set_index(int value)
{
	index = value;
}

auto ce::tileset::at(int i) const -> ce::image
{
	auto size_f = static_cast<float>(size);
	Rectangle rect{
		static_cast<float>(size * i), 0.F,
		size_f, size_f,
	};
	return ce::image(ImageFromImage(image, rect));
}

void ce::tileset::draw(int i) const
{
	texture.draw(size, size, size * i, 0);
}

void ce::tileset::draw(int i, float rotation, float scale) const
{
	texture.draw(size, size, size * i, 0, rotation, scale);
}

auto ce::tileset::get_size() const -> int
{
	return size;
}

void ce::tileset::set_pos(float x, float y)
{
	texture.set_x(x);
	texture.set_y(y);
}

void ce::tileset::move(float x, float y)
{
	texture.move(x, y);
}

auto ce::tileset::x() const -> float
{
	return texture.get_x();
}

auto ce::tileset::y() const -> float
{
	return texture.get_y();
}
