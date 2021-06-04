#include "sprite.hpp"

ce::sprite::sprite(const ce::texture &texture)
	: texture(texture),
	movable()
{
}

void ce::sprite::draw()
{
	texture.draw(get_x(), get_y());
}
