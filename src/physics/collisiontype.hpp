#pragma once

#include "chipmunk/chipmunk.h"

namespace phys
{
	enum class collision_type: cpCollisionType
	{
		one_way = 1,
		tile = 2,
		player = 4,
	};
}
