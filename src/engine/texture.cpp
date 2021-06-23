#include "texture.hpp"

ce::texture::texture(const asset::image &image)
	: r_texture(LoadTextureFromImage(image))
{
}

void ce::texture::draw(float x, float y)
{
	DrawTexture(r_texture,
		static_cast<int>(x),
		static_cast<int>(y),
		WHITE);
}

void ce::texture::draw(float x, float y, int size, int offset) const
{
	auto size_f = static_cast<float>(size);

	Rectangle rect{
		static_cast<float>(offset), 0.F,
		size_f, size_f,
	};

	Vector2 pos{
		x, y
	};

	DrawTextureRec(r_texture, rect, pos, WHITE);
}

void ce::texture::draw(float x, float y, int size, int offset,
	float rotation, float scale) const
{
	auto size_f = static_cast<float>(size);

	Rectangle rect{
		static_cast<float>(offset), 0.F,
		size_f, size_f,
	};

	Rectangle dest{
		x, y,
		size_f * scale,
		size_f * scale,
	};

	Vector2 orig{
		0, 0,
	};

	DrawTextureTiled(r_texture, rect, dest, orig, rotation, scale, WHITE);
}

auto ce::texture::get_width() const -> int
{
	return r_texture.width;
}

auto ce::texture::get_height() const -> int
{
	return r_texture.height;
}
