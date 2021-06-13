#include "physics/body.hpp"

phys::body::body(cpBody *body, cpShape *shape)
	: cp_body(body),
	cp_shape(shape)
{
	cpShapeSetUserData(cp_shape, this);
}

phys::body::~body()
{
	cpBodyFree(cp_body);
	cpShapeFree(cp_shape);
}

//region cpBody

auto phys::body::get_position() const -> ce::vector2f
{
	return ce::vector2f(cpBodyGetPosition(cp_body));
}

void phys::body::set_position(const ce::vector2f &position)
{
	cpBodySetPosition(cp_body, position.to_cp_vec());
}

void phys::body::set_velocity(const ce::vector2f &velocity)
{
	cpBodySetVelocity(cp_body, velocity.to_cp_vec());
}

//endregion

//region cpShape

void phys::body::set_elasticity(float value) const
{
	cpShapeSetElasticity(cp_shape, value);
}

void phys::body::set_friction(float value) const
{
	cpShapeSetFriction(cp_shape, value);
}

void phys::body::set_collision_type(phys::collision_type value) const
{
	cpShapeSetCollisionType(cp_shape, static_cast<cpCollisionType>(value));
}

void phys::body::set_filter(cpShapeFilter filter) const
{
	cpShapeSetFilter(cp_shape, filter);
}

//endregion

#ifndef NDEBUG
void phys::body::debug_draw(Color color)
{
	auto vertices = cpPolyShapeGetCount(cp_shape);
	for (auto v = 0; v < vertices; v++)
	{
		ce::vector2f v1(cpPolyShapeGetVert(cp_shape, v));
		ce::vector2f v2(cpPolyShapeGetVert(cp_shape,
			v + 1 < vertices ? v + 1 : 0));

		DrawLineV(v1.to_r_vec(), v2.to_r_vec(), color);
	}
}
#endif