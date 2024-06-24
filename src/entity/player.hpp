#pragma once

#include "engine/level.hpp"
#include "entity/hud.hpp"
#include "enum/tiletype.hpp"

#include <chirp/animatedsprite.hpp>
#include <chirp/assets.hpp>
#include <chirp/direction.hpp>
#include <chirp/scenemanager.hpp>

namespace entity
{
	class player: public chirp::animated_sprite
	{
	public:
		player(const chirp::assets &assets, const chirp::scene_manager &scenes,
			::entity::hud &hud, float scale);

		void update(const chirp::scene &scene, float delta) override;
		void draw() const override;

		[[nodiscard]]
		auto get_velocity() const -> const chirp::vector2f &;

		void set_velocity(const chirp::vector2f &value);

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

		tile_type colliding_tile_type;

		::entity::hud &hud;
		const chirp::scene_manager &scenes;

		chirp::vector2f velocity;

		chirp::asset<chirp::sound> snd_jump;
		chirp::asset<chirp::sound> snd_fall;

		void update_collision(ce::level &level);
		auto get_player_dir() const -> chirp::direction;
	};
}
