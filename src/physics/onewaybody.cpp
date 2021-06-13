#include "onewaybody.hpp"

phys::one_way_body::one_way_body(cpBody *body, cpShape *shape, const ce::vector2f &position)
	: static_body(body, shape, position),
	normal(0.F, 1.F)
{
}

auto phys::one_way_body::get_normal() const -> ce::vector2f
{
	return normal;
}
