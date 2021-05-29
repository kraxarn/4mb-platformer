#include "text.hpp"

ce::text::text(std::string text, int x, int y, int font_size, Color color)
	: str(std::move(text)), x(x), y(y), font_size(font_size), color(color)
{
}

void ce::text::draw()
{
	DrawText(str.c_str(), x, y, font_size, color);
}

void ce::text::set_text(const std::string &text)
{
	str = text;
}
