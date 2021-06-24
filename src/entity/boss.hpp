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
		const ce::movable &player;

		/** Get in what direction the player is */
		auto get_player_dir() const -> direction;
	};
}
