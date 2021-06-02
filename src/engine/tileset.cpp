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
	texture.draw_rect(size, size, size * i, 0);
}

auto ce::tileset::get_size() const -> int
{
	return size;
}
