#include "engine/physics.hpp"

// Timing is broken on Windows, so this works for now
#define PHYSAC_AVOID_TIMMING_SYSTEM

#ifndef NDEBUG
#define PHYSAC_DEBUG
#endif

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

ce::physics::physics()
{
	InitPhysics();
}

ce::physics::~physics()
{
	static_bodies.clear();
	dynamic_bodies.clear();
	ClosePhysics();
}

auto ce::physics::bodies_count() const -> int
{
	return GetPhysicsBodiesCount();
}

auto ce::physics::static_bodies_count() const -> std::size_t
{
	return static_bodies.size();
}

auto ce::physics::dynamic_body_count() const -> std::size_t
{
	return dynamic_bodies.size();
}

void ce::physics::update()
{
	UpdatePhysics();
}

void ce::physics::reset()
{
	ResetPhysics();
}

void ce::physics::add_static_body(const ce::vector2f &position, const ce::vector2f &size)
{
	static_bodies[position] = std::make_shared<ce::static_body>(position, size);
}

void ce::physics::add_dynamic_body(const ce::vector2f &position, const ce::vector2f &size)
{
	dynamic_bodies.push_back(std::make_shared<ce::dynamic_body>(position, size));
}

#ifndef NDEBUG

void ce::physics::draw() const
{
	for (auto i = 0; i < bodies_count(); i++)
	{
		auto *body = GetPhysicsBody(i);

		auto vertices = GetPhysicsShapeVerticesCount(i);
		for (int j = 0; j < vertices; j++)
		{
			DrawLineV(GetPhysicsShapeVertex(body, j),
				GetPhysicsShapeVertex(body, j + 1 < vertices ? j + 1 : 0),
				PINK);
		}
	}
}

#endif
