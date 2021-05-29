#include "text.hpp"

ce::text::text(std::string text, int x, int y, int font_size, Color color)
	: str(std::move(text)), x(x), y(y), font_size(font_size), color(color)
{
}

void ce::text::draw()
{
	DrawText(str.c_str(), x, y, font_size, color);
}

auto ce::text::get_text() const -> const std::string &
{
	return str;
}

void ce::text::set_text(const std::string &text)
{
	str = text;
}

auto ce::text::get_x() const -> int
{
	return x;
}

auto ce::text::get_y() const -> int
{
	return y;
}

auto ce::text::position() const -> Vector2
{
	return Vector2{
		static_cast<float>(get_x()),
		static_cast<float>(get_y()),
	};
}

auto ce::text::get_font_size() const -> int
{
	return font_size;
}

auto ce::text::get_color() const -> Color
{
	return color;
}
