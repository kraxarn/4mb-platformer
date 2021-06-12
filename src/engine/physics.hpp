#pragma once

#include "raylib.h"

#include "engine/staticbody.hpp"
#include "engine/dynamicbody.hpp"

#include <vector>
#include <memory>
#include <unordered_map>

namespace ce
{
	class physics
	{
	public:
		physics();
		~physics();

		auto bodies_count() const -> int;
		auto static_bodies_count() const -> std::size_t;
		auto dynamic_body_count() const -> std::size_t;

		void add_static_body(const ce::vector2f &position, const ce::vector2f &size);
		void add_dynamic_body(const ce::vector2f &position, const ce::vector2f &size);

		void update();
		void reset();

#ifndef NDEBUG
		void draw() const;
#endif

	private:
		std::unordered_map<ce::vector2f, std::shared_ptr<ce::static_body>> static_bodies;
		std::vector<std::shared_ptr<ce::dynamic_body>> dynamic_bodies;
	};
}
