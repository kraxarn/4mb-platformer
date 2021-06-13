#pragma once

#include "physics/body.hpp"

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
