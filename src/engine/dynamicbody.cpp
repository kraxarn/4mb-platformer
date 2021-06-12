#include "dynamicbody.hpp"

#include "physac.h"

ce::dynamic_body::dynamic_body(const ce::vector2f &position, const ce::vector2f &size)
	: ce::physics_body(position, size, 1.F)
{
	set_enabled(true);
}
