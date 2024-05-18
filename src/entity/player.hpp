#pragma once

#include "engine/assets.hpp"
#include "engine/animatedsprite.hpp"
#include "engine/map.hpp"
#include "engine/movable.hpp"
#include "engine/input.hpp"

#include "physics/collision.hpp"
#include "physics/tiles.hpp"
#include "enum/direction.hpp"
#include "entity/hud.hpp"
#include "entity/pause.hpp"

namespace entity
{
	class player: public ce::animated_sprite
	{
	public:
		player(const ce::assets &assets, entity::hud &hud, float scale);

		/** Update input, position, collision, and finally draw sprite */
		void update(const ce::input &input, ce::level &level,
			bool is_paused);

		/** Get current player speed */
		auto get_velocity() const -> const chirp::vector2f &;
		/** Is player on the ground */
		auto is_grounded() const -> bool;

	private:
		static constexpr float move_acceleration = 1.F;
		static constexpr float move_deceleration = -0.4F;

		static constexpr float jump_force = -10.F;
		static constexpr float gravity = 0.4F;

		static constexpr float speed_limit = 7.5F;

		/** Y position to kill the player at */
		static constexpr float kill_limit = 2'000.F;

		entity::hud &hud;

		chirp::vector2f velocity;

		chirp::sound snd_jump;
		chirp::sound snd_fall;

		void update_collision(ce::level &level);
		auto get_player_dir() const -> direction;
	};
}
