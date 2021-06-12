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
	static_bodies.push_back(std::make_shared<ce::static_body>(position, size));
}

auto ce::physics::add_dynamic_body(const ce::vector2f &position,
	const ce::vector2f &size) -> std::shared_ptr<ce::dynamic_body>
{
	dynamic_bodies.push_back(std::make_shared<ce::dynamic_body>(position, size));
	return dynamic_bodies.back();
}

void ce::physics::delete_outside(const ce::vector2i &offset, const ce::vector2i &size)
{
	for (auto &body : static_bodies)
	{
		if (!body)
		{
			continue;
		}

		// For now, we only care about position and not size
		// as it's in the corners and hopefully not noticeable anyway
		const auto pos = body->get_position().to<int>();

		if (pos.x < offset.x              // left
			|| pos.x > offset.x + size.x  // right
			|| pos.y > offset.y           // top
			|| pos.y < offset.y + size.y) // bottom
		{
//			body.reset();
//			static_bodies.erase(std::remove(static_bodies.begin(),
//				static_bodies.end(), body), static_bodies.end());
		}
	}
}

#ifndef NDEBUG
void ce::physics::draw() const
{
	for (const auto &body : static_bodies)
	{
		body->draw(PINK);
	}

	for (const auto &body : dynamic_bodies)
	{
		body->draw(GREEN);
	}
}
#endif
