#pragma once

#include "keymap.hpp"
#include "engine/animatedsprite.hpp"

#include "entity/hud.hpp"
#include "enum/direction.hpp"
#include "physics/collision.hpp"

#include <chirp/assets.hpp>

namespace entity
{
	class player: public ce::animated_sprite
	{
	public:
		player(const chirp::assets &assets, entity::hud &hud, float scale);

		/** Update input, position, collision, and finally draw sprite */
		void update(const keymap &keymap, ce::level &level,
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

		chirp::asset<chirp::sound> snd_jump;
		chirp::asset<chirp::sound> snd_fall;

		void update_collision(ce::level &level);
		auto get_player_dir() const -> direction;
	};
}
