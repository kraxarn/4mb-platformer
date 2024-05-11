#include "draw.hpp"

void ce::draw::begin()
{
	BeginDrawing();
}

void ce::draw::end()
{
	EndDrawing();
}

void ce::draw::clear(const chirp::color &color)
{
	ClearBackground(Color{
		.r = color.red(),
		.g = color.green(),
		.b = color.blue(),
		.a = color.alpha(),
	});
}

void ce::draw::clear(unsigned int color)
{
	clear({
		static_cast<unsigned char>(color >> 0b10000),
		static_cast<unsigned char>(color >> 0b01000),
		static_cast<unsigned char>(color),
	});
}

void ce::draw::text(const std::string &text, int x, int y, int fontSize, Color color)
{
	DrawText(text.c_str(), x, y, fontSize, color);
}
