#pragma once

#include "engine/physicsbody.hpp"

namespace ce
{
	/**
	 * Static physics body
	 */
	class static_body: public ce::physics_body
	{
	public:
		static_body(const ce::vector2f &position, const ce::vector2f &size);
	};
}
