#pragma once

#include "raylib.h"
#include "physac.h"

#include "engine/vector2.hpp"
#include "engine/physicsconfig.hpp"

namespace ce
{
	class physics_body
	{
	public:
		auto get_position() const -> ce::vector2f;
		void set_position(const ce::vector2f &position) const;

		void add_force(const ce::vector2f &force) const;

		auto is_grounded() const -> bool;

#ifndef NDEBUG
		void draw_shape(Color color) const;
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
