#include "sprite.hpp"

ce::sprite::sprite(const ce::texture &texture)
	: texture(texture),
	movable()
{
}

ce::sprite::sprite(const ce::image &image)
	: ce::sprite(ce::texture(image))
{
}

void ce::sprite::draw()
{
	texture.draw(get_x(), get_y());
}
