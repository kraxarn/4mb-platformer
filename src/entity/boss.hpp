#pragma once

#include "engine/movable.hpp"
#include "engine/assets.hpp"
#include "engine/animatedsprite.hpp"
#include "level/level10.hpp"

namespace entity
{
	class boss: public ce::animated_sprite
	{
	public:
		boss(const ce::assets &assets, const ce::movable &player, float scale);

		void update();

		void set_lock_y(bool value);

		/** Is final boss */
		static auto is_final(const ce::level *level) -> bool;

	private:
		static constexpr float move_speed = 1.F;

		const ce::movable &player;

		/** Is locked in the Y-axis */
		bool lock_y = false;

		/** Get in what directions player is */
		auto get_player_dirs() const -> direction;

		/** Get distance to player, always positive */
		auto get_player_dist() const -> ce::vector2f;

		static auto eq(const direction &dir1, const direction &dir2) -> bool;
	};
}
