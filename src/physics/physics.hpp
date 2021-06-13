#pragma once

#include "chipmunk/chipmunk.h"

#include "engine/vector2.hpp"
#include "physics/config.hpp"
#include "physics/staticbody.hpp"
#include "physics/dynamicbody.hpp"
#include "physics/onewaybody.hpp"

#include <vector>
#include <memory>
#include <algorithm>

namespace phys
{
	class physics
	{
	public:
		physics();
		~physics();

		/** Clear all static and dynamic bodies in space */
		void clear();

		auto static_bodies_count() const -> std::size_t;
		auto dynamic_body_count() const -> std::size_t;

		void add_static_body(const ce::vector2f &size, const ce::vector2f &position);
		auto add_dynamic_body(const ce::vector2f &size) -> std::shared_ptr<phys::dynamic_body>;

		void update(double delta_time) const;
	private:
		cpSpace *cp_space = nullptr;
		cpCollisionHandler *cp_handler = nullptr;

		std::vector<std::shared_ptr<phys::static_body>> static_bodies;
		std::vector<std::shared_ptr<phys::dynamic_body>> dynamic_bodies;

		/** Pre-solve handler for collision_type::one_way */
		static auto pre_solve_one_way(cpArbiter *arbiter, cpSpace *space,
			void *ignore) -> cpBool;
	};
}
