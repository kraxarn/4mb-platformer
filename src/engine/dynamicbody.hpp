#pragma once

#include "raylib.h"

#include "engine/physicsbody.hpp"

namespace ce
{
	/**
	 * Dynamic physics body
	 */
	class dynamic_body: public ce::physics_body
	{
	public:
		dynamic_body(const ce::vector2f &position, const ce::vector2f &size);
	};
}
