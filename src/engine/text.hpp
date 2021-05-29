#pragma once

#include "raylib.h"

#include <string>
#include <utility>

namespace ce
{
	class text
	{
	public:
		text(std::string text, int x, int y, int font_size, Color color);

		void draw();

		void set_text(const std::string &text);

	private:
		std::string str;
		int x = 0;
		int y = 0;
		int font_size = 0;
		Color color;
	};
}
