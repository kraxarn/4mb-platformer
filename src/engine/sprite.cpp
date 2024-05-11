#include "sprite.hpp"

ce::sprite::sprite(const ce::texture &texture)
	: texture(texture),
	movable()
{
}

ce::sprite::sprite(const chirp::image &image)
	: ce::sprite(ce::texture(image))
{
}

void ce::sprite::draw()
{
	texture.draw(get_x(), get_y());
}

auto ce::sprite::width() const -> int
{
	return texture.get_width();
}

auto ce::sprite::height() const -> int
{
	return texture.get_height();
}
