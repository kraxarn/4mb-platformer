#include "asset/tileset.hpp"

asset::tileset::tileset(const std::vector<unsigned char> &data)
	: image(data),
	texture(image)
{
	size = texture.get_height();
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

void asset::tileset::draw(float x, float y, int i, float rotation, float scale) const
{
	texture.draw(x, y, size, size * i, rotation, scale);
}

void asset::tileset::flip_horizontal()
{
	ImageFlipHorizontal(&image);
	texture = ce::texture(image);
}

auto asset::tileset::get_size() const -> int
{
	return size;
}
