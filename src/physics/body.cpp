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

/*
void ce::physics_body::set_enabled(bool enabled) const
{
	GetPhysicsBody(id)->enabled = enabled;
}

auto ce::physics_body::get_position() const -> ce::vector2f
{
	const auto *body = GetPhysicsBody(id);
	return {
		body->position.x * ce::phys::scale,
		body->position.y * ce::phys::scale,
	};
}

void ce::physics_body::set_position(const ce::vector2f &position) const
{
	auto *body = GetPhysicsBody(id);
	body->position.x = position.x / ce::phys::scale;
	body->position.y = position.y / ce::phys::scale;
}

void ce::physics_body::add_force(const ce::vector2f &force) const
{
	auto *body = GetPhysicsBody(id);
	body->velocity.x += force.x;
	body->velocity.y += force.y;
}

auto ce::physics_body::is_grounded() const -> bool
{
	return GetPhysicsBody(id)->isGrounded;
}

#ifndef NDEBUG
void ce::physics_body::draw_shape(Color color) const
{
	auto *body = GetPhysicsBody(id);
	auto vertices = GetPhysicsShapeVerticesCount(id);

	for (int j = 0; j < vertices; j++)
	{
		auto v1 = ce::vector2f(GetPhysicsShapeVertex(body, j)) * ce::phys::scale;
		auto v2 = ce::vector2f(GetPhysicsShapeVertex(body,
			j + 1 < vertices ? j + 1 : 0)) * ce::phys::scale;

		DrawLineV(v1.to_r_vec(), v2.to_r_vec(), color);
	}
}
#endif
*/
