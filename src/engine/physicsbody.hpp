#pragma once

#include "raylib.h"
#include "physac.h"

#include "engine/vector2.hpp"

namespace ce
{
	class physics_body
	{
	public:
		auto get_position() const -> ce::vector2f;

#ifndef NDEBUG
		void draw(Color color) const;
#endif

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
