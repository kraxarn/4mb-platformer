#include "staticbody.hpp"

phys::static_body::static_body(cpBody *body, cpShape *shape, const ce::vector2f &position)
	: phys::body(body, shape)
{
	set_elasticity(1.F);
	set_friction(1.F);
	set_position(position);
}
