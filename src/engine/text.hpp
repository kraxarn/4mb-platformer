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

		auto get_text() const -> const std::string &;
		void set_text(const std::string &text);

		auto get_x() const -> int;
		void set_x(int value);

		auto get_y() const -> int;
		void set_y(int value);

		auto position() const -> Vector2;

		auto get_font_size() const -> int;

		auto get_color() const -> Color;

	private:
		std::string str;
		int x = 0;
		int y = 0;
		int font_size = 0;
		Color color;
	};
}
