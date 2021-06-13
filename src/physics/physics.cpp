#include "physics/physics.hpp"

phys::physics::physics()
{
	cp_space = cpSpaceNew();

	cpSpaceSetIterations(cp_space, phys::iterations);
	cpSpaceSetGravity(cp_space, cpv(0, phys::gravity));

	cp_handler = cpSpaceAddWildcardHandler(cp_space,
		static_cast<cpCollisionType>(collision_type::one_way));
	cp_handler->preSolveFunc = phys::physics::pre_solve_one_way;
}

phys::physics::~physics()
{
	clear();
	cpSpaceFree(cp_space);
}

void phys::physics::clear()
{
	static_bodies.clear();
	dynamic_bodies.clear();
}

auto phys::physics::static_bodies_count() const -> std::size_t
{
	return static_bodies.size();
}

auto phys::physics::dynamic_body_count() const -> std::size_t
{
	return dynamic_bodies.size();
}

void phys::physics::add_static_body(const ce::vector2f &size, const ce::vector2f &position)
{
	auto *body = cpBodyNewStatic();
	cpSpaceAddBody(cp_space, body);
	cpBodySetPosition(body, position.to_cp_vec());

	auto *shape = cpBoxShapeNew(body, size.x, size.y, 0.F);
	cpSpaceAddShape(cp_space, shape);

	static_bodies.push_back(std::make_shared<phys::static_body>(body, shape));
}

auto phys::physics::add_dynamic_body(const ce::vector2f &size)
-> std::shared_ptr<phys::dynamic_body>
{
	constexpr float body_mass = 10.F;

	auto moment = cpMomentForBox(body_mass, size.x, size.y);
	auto *body = cpBodyNew(body_mass, moment);
	cpSpaceAddBody(cp_space, body);

	auto *shape = cpBoxShapeNew(body, size.x, size.y, 12.F);
	cpSpaceAddShape(cp_space, shape);

	dynamic_bodies.push_back(std::make_shared<phys::dynamic_body>(body, shape));
	return dynamic_bodies.back();
}

void phys::physics::update(double delta_time) const
{
	cpSpaceStep(cp_space, delta_time);
}

auto phys::physics::pre_solve_one_way(cpArbiter *arbiter, cpSpace */*space*/,
	void */*data*/) -> cpBool
{
	cpShape *shape;
	cpArbiterGetShapes(arbiter, &shape, nullptr);

	auto *body = (phys::one_way_body *) cpShapeGetUserData(shape);
	if (cpvdot(cpArbiterGetNormal(arbiter), body->get_normal().to_cp_vec()) < 0)
	{
		return cpArbiterIgnore(arbiter);
	}
	return cpTrue;
}

#ifndef NDEBUG
void phys::physics::debug_draw()
{
	for (const auto &body : static_bodies)
	{
		body->debug_draw(PINK);
	}

	for (const auto &body : dynamic_bodies)
	{
		body->debug_draw(GREEN);
	}
}
#endif
