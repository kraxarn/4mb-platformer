#include "texture.hpp"

ce::texture::texture(const ce::image &image)
	: r_texture(LoadTextureFromImage(image))
{
}

void ce::texture::draw()
{
	DrawTexture(r_texture, x, y, WHITE);
}

void ce::texture::set_x(int value)
{
	x = value;
}

auto ce::texture::get_x() const -> int
{
	return x;
}

void ce::texture::set_y(int value)
{
	y = value;
}

auto ce::texture::get_y() const -> int
{
	return y;
}

void ce::texture::move(int x_offset, int y_offset)
{
	x += x_offset;
	y += y_offset;
}

auto ce::texture::get_width() const -> int
{
	return r_texture.width;
}

auto ce::texture::get_height() const -> int
{
	return r_texture.height;
}
