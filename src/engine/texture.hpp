#pragma once

#include "raylib.h"
#include "engine/image.hpp"

#include <cmath>

namespace ce
{
	class texture
	{
	public:
		explicit texture(const ce::image &image);

		void draw();

		void set_x(float value);
		auto get_x() const -> float;

		void set_y(float value);
		auto get_y() const -> float;

		void move(float x_offset, float y_offset);

		auto get_width() const -> int;
		auto get_height() const -> int;

	private:
		Texture2D r_texture;

		float x = 0;
		float y = 0;
	};
}
