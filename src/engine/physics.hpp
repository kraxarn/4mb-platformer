#pragma once

#include "raylib.h"

namespace ce
{
	class physics
	{
	public:
		physics();
		~physics();

		auto bodies_count() const -> int;

		void update();
		void reset();
	};
}
