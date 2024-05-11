#pragma once

#include "raylib.h"

#include <chirp/vector2.hpp>

namespace ce
{
	class camera
	{
	public:
		camera();

		void begin() const;
		void end() const;

		void set_target(const chirp::vector2f &target);

		auto get_offset() const -> chirp::vector2f;
		void set_offset(const chirp::vector2f &offset);

		void move(float x, float y);

		auto get_x() const -> float;
		void set_y(float y);

		auto get_y() const -> float;
		void set_x(float x);

		void zoom(float amount);

	private:
		Camera2D r_camera = {0};
	};
}
