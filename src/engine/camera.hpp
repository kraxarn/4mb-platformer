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
		void set_offset(const ce::vector2f &offset);

		void move(float x, float y);

	private:
		Camera2D r_camera = {0};
	};
}
