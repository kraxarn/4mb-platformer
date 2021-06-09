#include "engine/physics.hpp"

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
