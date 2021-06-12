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
	ce::iterate_map_all<std::size_t, std::shared_ptr<ce::static_body>>(static_bodies, [this]
		(std::size_t /*x*/, std::size_t /*y*/, std::shared_ptr<ce::static_body> body)
	{
		if (body)
		{
			body.reset();
			num_static--;
		}
	});

	ce::iterate_map_all<std::size_t, std::shared_ptr<ce::dynamic_body>>(dynamic_bodies, [this]
		(std::size_t /*x*/, std::size_t /*y*/, std::shared_ptr<ce::dynamic_body> body)
	{
		if (body)
		{
			body.reset();
			num_dynamic--;
		}
	});

	ClosePhysics();
}

void ce::physics::set_scale(float scale)
{
	world_scale = scale;
}

auto ce::physics::bodies_count() const -> int
{
	return GetPhysicsBodiesCount();
}

auto ce::physics::static_bodies_count() const -> std::size_t
{
	return num_static;
}

auto ce::physics::dynamic_body_count() const -> std::size_t
{
	return num_dynamic;
}

void ce::physics::update()
{
	UpdatePhysics();
}

void ce::physics::reset()
{
	ResetPhysics();
}

void ce::physics::add_static_body(const ce::vector2i &position, const ce::vector2f &size)
{
	auto pos = position.to<std::size_t>();
	static_bodies.at(pos.x).at(pos.y) =
		std::make_shared<ce::static_body>(position.to<float>() * world_scale, size);
	num_static++;
}

void ce::physics::add_dynamic_body(const ce::vector2i &position, const ce::vector2f &size)
{
	auto pos = position.to<std::size_t>();
	dynamic_bodies.at(pos.x).at(pos.y) =
		std::make_shared<ce::dynamic_body>(position.to<float>() * world_scale, size);
	num_dynamic++;
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
