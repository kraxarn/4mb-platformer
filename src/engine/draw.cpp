#include "draw.hpp"

void ce::draw::begin()
{
	BeginDrawing();
}

void ce::draw::end()
{
	EndDrawing();
}

void ce::draw::clear(Color color)
{
	ClearBackground(color);
}

void ce::draw::text(const std::string &text, int x, int y, int fontSize, Color color)
{
	DrawText(text.c_str(), x, y, fontSize, color);
}
