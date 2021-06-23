#pragma once

#include "engine/assets.hpp"
#include "engine/animatedsprite.hpp"
#include "engine/map.hpp"
#include "engine/movable.hpp"
#include "engine/input.hpp"

#include "physics/collision.hpp"

namespace entity
{
	class player: public ce::animated_sprite
	{
	public:
		player(const ce::assets &assets, float scale);

		/** Update input, position, collision, and finally draw sprite */
		void update(const ce::input &input, const ce::level &level);

		/** Get current player speed */
		auto get_velocity() const -> const ce::vector2f &;
		/** Is player on the ground */
		auto is_grounded() const -> bool;

		/** Get collision rectangle */
		auto rect() const -> Rectangle;

#ifndef NDEBUG
		auto get_collides() const -> const ce::vector2<bool> &;
#endif

	private:
		static constexpr float move_acceleration = 1.F;
		static constexpr float move_deceleration = -0.4F;

		static constexpr float jump_force = -10.F;
		static constexpr float gravity = 0.4F;

		static constexpr float speed_limit = 8.F;

		ce::vector2f velocity;

		asset::sound snd_jump;

		void update_collision(const ce::level &level);

#ifndef NDEBUG
		ce::vector2<bool> collides;

		static void debug_draw(const Rectangle &rect, const Color &color);
#endif
	};
}
