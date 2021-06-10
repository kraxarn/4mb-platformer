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

void ce::physics::update()
{
	UpdatePhysics();
}

void ce::physics::reset()
{
	ResetPhysics();
}

auto ce::physics::add_static_body(const ce::vector2f &position,
	const ce::vector2f &size) -> ce::static_body &
{
	static_bodies.emplace_back(position, size);
	return static_bodies.back();
}

auto ce::physics::add_dynamic_body(const ce::vector2f &position,
	const ce::vector2f &size) -> ce::dynamic_body &
{
	dynamic_bodies.emplace_back(position, size);
	return dynamic_bodies.back();
}
