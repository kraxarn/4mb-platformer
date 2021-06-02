#include "texture.hpp"

ce::texture::texture(const ce::image &image)
	: r_texture(LoadTextureFromImage(image))
{
}

void ce::texture::draw()
{
	DrawTexture(r_texture,
		static_cast<int>(x),
		static_cast<int>(y),
		WHITE);
}

void ce::texture::draw_rect(int w, int h, int x_pos, int y_pos) const
{
	Rectangle rect{
		static_cast<float>(x_pos),
		static_cast<float>(y_pos),
		static_cast<float>(w),
		static_cast<float>(h),
	};

	Vector2 pos{
		x, y
	};

	DrawTextureRec(r_texture, rect, pos, WHITE);
}

void ce::texture::set_x(float value)
{
	x = value;
}

auto ce::texture::get_x() const -> float
{
	return x;
}

void ce::texture::set_y(float value)
{
	y = value;
}

auto ce::texture::get_y() const -> float
{
	return y;
}

void ce::texture::move(float x_offset, float y_offset)
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
