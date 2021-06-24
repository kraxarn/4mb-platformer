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

		static auto eq(const direction &dir1, const direction &dir2) -> bool;
	};
}
