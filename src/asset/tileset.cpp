#include "asset/tileset.hpp"

asset::tileset::tileset(const cmrc::file &file)
	: image(file),
	texture(image)
{
	size = texture.get_height();
	count = texture.get_width() / size;
}

void asset::tileset::set_index(int value)
{
	index = value;
}

auto asset::tileset::at(int i) const -> asset::image
{
	auto size_f = static_cast<float>(size);
	Rectangle rect{
		static_cast<float>(size * i), 0.F,
		size_f, size_f,
	};

	return asset::image(ImageFromImage(image, rect));
}

void asset::tileset::draw(float x, float y, int i) const
{
	texture.draw(x, y, size, size * i);
}

void asset::tileset::draw(float x, float y, int i, float rotation, float scale) const
{
	texture.draw(x, y, size, size * i, rotation, scale);
}

auto asset::tileset::get_size() const -> int
{
	return size;
}
