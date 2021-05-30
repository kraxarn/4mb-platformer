#include "texture.hpp"

ce::texture::texture(const ce::image &image)
	: Texture2D(LoadTextureFromImage(image))
{
}
