#include "raylib.h"

auto main(int argc, char **argv) -> int
{
	InitWindow(1280, 720, "4mb-platformer");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		{
			DrawText(":3", 190, 200, 20, RAYWHITE);
		}
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
