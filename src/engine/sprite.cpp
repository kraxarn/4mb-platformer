#include "sprite.hpp"

ce::sprite::sprite(const chirp::texture &texture)
	: texture(texture),
	movable()
{
}

ce::sprite::sprite(const chirp::asset<chirp::image> &image)
	: ce::sprite(chirp::texture(image))
{
}

void ce::sprite::draw()
{
	texture.draw({get_x(), get_y()});
}

auto ce::sprite::width() const -> int
{
	return texture.size().x();
}

auto ce::sprite::height() const -> int
{
	return texture.size().y();
}
