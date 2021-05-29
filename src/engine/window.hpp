#pragma once

#include "raylib.h"

#include <string>

namespace ce
{
	class window
	{
	public:
		window(int width, int height, const std::string &title, int fps);
		window(int width, int height, const std::string &title);

		~window();

		static auto should_close() -> bool;
	};
}
