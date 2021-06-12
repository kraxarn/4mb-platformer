#pragma once

#include "raylib.h"

#include "engine/staticbody.hpp"
#include "engine/dynamicbody.hpp"
#include "engine/map.hpp"

#include <vector>
#include <memory>

namespace ce
{
	class physics
	{
	public:
		physics();
		~physics();

		void set_scale(float scale);

		auto bodies_count() const -> int;
		auto static_bodies_count() const -> std::size_t;
		auto dynamic_body_count() const -> std::size_t;

		void add_static_body(const ce::vector2i &position, const ce::vector2f &size);
		void add_dynamic_body(const ce::vector2i &position, const ce::vector2f &size);

		void update();
		void reset();

#ifndef NDEBUG
		void draw() const;
#endif

	private:
		float world_scale = 1.F;

		ce::map<std::shared_ptr<ce::static_body>> static_bodies;
		ce::map<std::shared_ptr<ce::dynamic_body>> dynamic_bodies;

		std::size_t num_static = 0;
		std::size_t num_dynamic = 0;
	};
}
