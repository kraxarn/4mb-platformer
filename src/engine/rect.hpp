#pragma once

#include "raylib.h"

#include "engine/vector2.hpp"
#include "engine/movable.hpp"
#include "engine/animatedsprite.hpp"

namespace ce
{
	class rect
	{
	public:
		template<typename T>
		static auto get(const T &item) -> Rectangle
		{
			const ce::movable &movable = item;
			const ce::animated_sprite &sprite = item;

			return Rectangle{
				movable.get_x(),
				movable.get_y(),
				static_cast<float>(sprite.width()),
				static_cast<float>(sprite.height()),
			};
		}
	};
}
