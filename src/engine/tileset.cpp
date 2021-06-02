#include "tileset.hpp"

ce::tileset::tileset(const cmrc::file &file)
	: texture(ce::image(file))
{
	size = texture.get_height();
	count = texture.get_width() / size;
}
