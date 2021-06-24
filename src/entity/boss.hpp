#pragma once

#include "engine/movable.hpp"
#include "engine/assets.hpp"
#include "engine/animatedsprite.hpp"

namespace entity
{
	class boss: public ce::animated_sprite
	{
	public:
		boss(const ce::assets &assets, const ce::movable &player, float scale);

		void update();

	private:
		static constexpr float move_speed = 1.F;

		const ce::movable &player;

		/** Get in what directions player is */
		auto get_player_dirs() const -> direction;

		/** Get distance to player, always positive */
		auto get_player_dist() const -> ce::vector2f;

		static auto eq(const direction &dir1, const direction &dir2) -> bool;
	};
}
