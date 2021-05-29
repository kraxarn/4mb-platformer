#include "window.hpp"

ce::window::window(int width, int height, const std::string &title, int fps)
{
	InitWindow(width, height, title.c_str());
	SetTargetFPS(fps);
}

ce::window::window(int width, int height, const std::string &title)
	: window(width, height, title, 60)
{
}

ce::window::~window()
{
	CloseWindow();
}

auto ce::window::should_close() -> bool
{
	return WindowShouldClose();
}
