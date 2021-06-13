#pragma once

#include "chipmunk/chipmunk.h"

#include "engine/vector2.hpp"
#include "physics/collisiontype.hpp"

namespace phys
{
	class body
	{
	public:
		//region Body

		auto get_position() const -> ce::vector2f;
		void set_position(const ce::vector2f &position);

		void set_velocity(const ce::vector2f &velocity);

		//endregion

		//region Shape

		void set_elasticity(float value) const;

		void set_friction(float value) const;

		void set_collision_type(phys::collision_type value) const;

		void set_filter(cpShapeFilter filter) const;

		//endregion

		/*
		auto get_position() const -> ce::vector2f;
		void set_position(const ce::vector2f &position) const;

		void add_force(const ce::vector2f &force) const;

		auto is_grounded() const -> bool;

#ifndef NDEBUG
		void draw_shape(Color color) const;
#endif
		 */

	protected:
		body(cpBody *body, cpShape *shape);
		~body();

		/*
		void set_enabled(bool enabled) const;
		 */

	private:
		cpBody *cp_body = nullptr;
		cpShape *cp_shape = nullptr;
	};
}
