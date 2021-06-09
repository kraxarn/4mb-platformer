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
