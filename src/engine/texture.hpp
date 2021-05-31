#pragma once

#include "raylib.h"
#include "engine/image.hpp"

namespace ce
{
	class texture
	{
	public:
		explicit texture(const ce::image &image);

		void draw();

		void set_x(int value);
		auto get_x() const -> int;

		void set_y(int value);
		auto get_y() const -> int;

		void move(int x_offset, int y_offset);

		auto get_width() const -> int;
		auto get_height() const -> int;

	private:
		Texture2D r_texture;

		int x = 0;
		int y = 0;
	};
}
