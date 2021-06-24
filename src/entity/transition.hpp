#pragma once

#include "raylib.h"
#include "engine/vector2.hpp"
#include "engine/window.hpp"

#include <functional>

namespace entity
{
	class transition
	{
	public:
		transition() = default;

		void expand(const ce::vector2f &end, std::function<void()> callback);
		void shrink(const ce::vector2f &end, std::function<void()> callback);

		void update();

	private:
		enum class direction
		{
			none,
			expanding,
			shrinking,
		};
		direction dir = direction::none;

		ce::vector2i position;
		float size = 0.F;
		float speed = 0;

		std::function<void()> expand_callback;
		std::function<void()> shrink_callback;
	};
}
