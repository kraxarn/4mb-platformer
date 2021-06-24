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

namespace entity
{
	class player: public ce::animated_sprite
	{
	public:
		player(const ce::assets &assets, entity::hud &hud, float scale);

		/** Update input, position, collision, and finally draw sprite */
		void update(const ce::input &input, ce::level &level);

		/** Get current player speed */
		auto get_velocity() const -> const ce::vector2f &;
		/** Is player on the ground */
		auto is_grounded() const -> bool;

		/** Get collision rectangle */
		auto rect() const -> Rectangle;

	private:
		static constexpr float move_acceleration = 1.F;
		static constexpr float move_deceleration = -0.4F;

		static constexpr float jump_force = -10.F;
		static constexpr float gravity = 0.4F;

		static constexpr float speed_limit = 8.F;

		/** Y position to kill the player at */
		static constexpr float kill_limit = 2'000.F;

		entity::hud &hud;

		ce::vector2f velocity;
		direction dir;

		asset::sound snd_jump;

		void update_collision(ce::level &level);
		auto get_dir() const -> direction;

#ifndef NDEBUG
		static void debug_draw(const Rectangle &rect, const Color &color);
#endif
	};
}
