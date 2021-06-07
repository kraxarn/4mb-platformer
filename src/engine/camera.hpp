#pragma once

#include "raylib.h"

#include "engine/vector2.hpp"

namespace ce
{
	class camera
	{
	public:
		camera();

		void begin() const;
		void end() const;

		void set_target(const ce::vector2f &target);

		auto get_offset() const -> ce::vector2f;
		void set_offset(const ce::vector2f &offset);

		void move(float x, float y);

		auto get_x() const -> float;
		void set_y(float y);

		auto get_y() const -> float;
		void set_x(float x);

	private:
		Camera2D r_camera = {0};
	};
}
