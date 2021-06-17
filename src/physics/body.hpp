#pragma once

#include "chipmunk/chipmunk.h"

#include "engine/vector2.hpp"
#include "physics/collisiontype.hpp"
#include "physics/config.hpp"

namespace phys
{
	class body
	{
	public:
		//region Body

		auto get_position() const -> ce::vector2f;
		void set_position(const ce::vector2f &position);

		auto get_force() const -> ce::vector2f;
		void set_force(const ce::vector2f &force);

		//endregion

		//region Shape

		void set_elasticity(float value) const;

		void set_friction(float value) const;

		void set_filter(cpShapeFilter filter) const;

		//endregion

#ifndef NDEBUG
		void debug_draw(Color color);
#endif

	protected:
		body(cpBody *body, cpShape *shape);
		~body();

	private:
		cpBody *cp_body = nullptr;
		cpShape *cp_shape = nullptr;
	};
}
