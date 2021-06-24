#include "window.hpp"

ce::window::window(int width, int height, const std::string &title, int fps)
{
	InitWindow(width, height, title.c_str());
	SetTargetFPS(fps);
	SetExitKey(KEY_Q);
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

void ce::window::begin() const
{
	BeginDrawing();
}

void ce::window::end() const
{
	EndDrawing();
}

void ce::window::close()
{
	CloseWindow();
}

void ce::window::set_icon(const asset::image &image)
{
	SetWindowIcon(image);
}

auto ce::window::size() -> ce::vector2i
{
	return {
		GetScreenWidth(),
		GetScreenHeight()
	};
}
