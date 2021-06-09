#include "staticbody.hpp"

ce::static_body::static_body(const ce::vector2f &position, const ce::vector2f &size)
	: ce::physics_body(position, size, 0.F)
{
	set_enabled(false);
}
