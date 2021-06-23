#include "asset/font.hpp"

asset::font::font(const cmrc::file &file, int font_size)
{
	r_font = LoadFontFromMemory(".ttf",
		(const unsigned char *) file.cbegin(),
		(int) file.size(),
		font_size, font_chars, 0x100);

	SetTextureFilter(r_font.texture, TEXTURE_FILTER_POINT);
}

asset::font::~font()
{
	UnloadFont(r_font);
	RL_FREE(font_chars);
}

void asset::font::draw_text(const ce::text &text) const
{
	DrawTextEx(r_font, text.get_text().c_str(), text.position(),
		static_cast<float>(text.get_font_size()),
		0.F, text.get_color());
}

auto asset::font::font_size() const -> int
{
	return r_font.baseSize;
}

auto asset::font::text_size(const ce::text &text) const -> Vector2
{
	return MeasureTextEx(r_font, text.get_text().c_str(),
		static_cast<float>(text.get_font_size()), 0.F);
}
