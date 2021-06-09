#pragma once

#include "raylib.h"
#include "physac.h"

#include "engine/vector2.hpp"

namespace ce
{
	class physics_body
	{
	protected:
		/**
		 * Create a new rectangle body
		 */
		physics_body(const ce::vector2f &position, const ce::vector2f &size, float density);
		~physics_body();

		void set_enabled(bool enabled) const;

	private:
		int id = -1;
	};
}
