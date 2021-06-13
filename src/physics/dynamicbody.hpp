#pragma once

#include "physics/body.hpp"
#include "engine/vector2.hpp"

namespace phys
{
	/**
	 * Dynamic physics body
	 */
	class dynamic_body: public phys::body
	{
	public:
		dynamic_body(cpBody *body, cpShape *shape);
	};
}
