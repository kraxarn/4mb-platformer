#pragma once

#include "raylib.h"

#include <string>

namespace ce
{
	class draw
	{
	public:
		static void begin();
		static void end();

		static void clear(Color color);
		static void clear(unsigned int color);

		static void text(const std::string &text, int x, int y, int fontSize, Color color);

	private:
		draw() = default;
	};
}
