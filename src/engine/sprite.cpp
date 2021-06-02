#include "sprite.hpp"

ce::sprite::sprite(const ce::tileset &tileset)
	: tileset(tileset)
{
}

void ce::sprite::draw()
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

	tileset.draw(frame);
}
