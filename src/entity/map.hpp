#pragma once

#include "engine/level.hpp"

#include <chirp/assets.hpp>
#include <chirp/entity.hpp>

namespace entity
{
	class map: public chirp::entity
	{
	public:
		map() = default;
		~map() override;

		void update(const chirp::scene &scene, float delta) override;
		void draw() const override;

		[[nodiscard]]
		auto get_level() const -> ce::level *;

		void set_level(const chirp::assets &assets, ce::level *level);

	private:
		ce::level *level = nullptr;

		chirp::asset<chirp::tileset> tiles;
		chirp::asset<chirp::tileset> items;

		int gem_count = 0;
	};
}
