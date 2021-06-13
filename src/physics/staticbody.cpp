#include "staticbody.hpp"

phys::static_body::static_body(cpBody *body, cpShape *shape)
	: phys::body(body, shape)
{
	set_elasticity(1.F);
	set_friction(1.F);
}
