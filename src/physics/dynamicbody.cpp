#include "physics/dynamicbody.hpp"

phys::dynamic_body::dynamic_body(cpBody *body, cpShape *shape)
	: phys::body(body, shape)
{
	set_elasticity(0.F);
	set_friction(0.9F);
}
