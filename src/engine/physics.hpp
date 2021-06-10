#pragma once

#include "raylib.h"

#include "engine/staticbody.hpp"
#include "engine/dynamicbody.hpp"

#include <vector>

namespace ce
{
	class physics
	{
	public:
		physics();
		~physics();

		auto bodies_count() const -> int;

		auto add_static_body(const ce::vector2f &position,
			const ce::vector2f &size) -> ce::static_body &;

		auto add_dynamic_body(const ce::vector2f &position,
			const ce::vector2f &size) -> ce::dynamic_body &;

		void update();
		void reset();

	private:
		std::vector<ce::static_body> static_bodies;
		std::vector<ce::dynamic_body> dynamic_bodies;
	};
}
