#pragma once

#include "physics/body.hpp"

namespace phys
{
	/**
	 * Static physics body
	 */
	class static_body: public phys::body
	{
	public:
		static_body(cpBody *body, cpShape *shape);
	};
}
