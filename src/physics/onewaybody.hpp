#pragma once

#include "physics/staticbody.hpp"
#include "engine/vector2.hpp"

namespace phys
{
	class one_way_body: public phys::static_body
	{
	public:
		one_way_body(cpBody *body, cpShape *shape, const ce::vector2f &position);

		auto get_normal() const -> ce::vector2f;

	private:
		ce::vector2f normal;
	};
}
