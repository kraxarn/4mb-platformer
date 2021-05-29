#include "window.hpp"

ce::window::window(int width, int height, const std::string &title, int fps)
{
	InitWindow(width, height, title.c_str());
	SetTargetFPS(fps);

//	camera.zoom = static_cast<float>(height) / render_height;
//	std::cout << "Using " << camera.zoom << "x scale" << std::endl;
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
	//BeginMode2D(camera);
}

void ce::window::end() const
{
	//EndMode2D();
	EndDrawing();
}
