#pragma once

#include <chirp/animatedsprite.hpp>
#include <chirp/assets.hpp>

namespace entity
{
	class boss: public chirp::animated_sprite
	{
	public:
		boss(const chirp::assets &assets, const chirp::vector2f &player_pos, float scale);

		void update(bool is_paused, float delta);

		void draw() const;

		/**
		 * Damage boss
		 * @return Boss died
		 */
		auto hurt() -> bool;

		void set_lock_y(bool value);

		/** Is final boss */
		static auto is_final(const chirp::level *level) -> bool;

	private:
		static constexpr float min_speed = 1.F;
		static constexpr float max_speed = 8.F;

		static constexpr int initial_health = 5;

		/** Minimum distance to move after getting hit */
		static constexpr int min_random_move = 400;
		/** Maximum distance to move after getting hit */
		static constexpr int max_random_move = 600;

		const chirp::vector2f &player_pos;

		chirp::asset<chirp::sound> snd_boss;

		/** Remaining hit points */
		int health = initial_health;
		/** Is locked in the Y-axis */
		bool lock_y = false;

		/** Get in what directions player is */
		auto get_player_dirs() const -> chirp::direction;

		/** Get distance to player, always positive */
		auto get_player_dist() const -> chirp::vector2f;

		/** Get random pos some place away from player */
		auto get_random_pos() const -> chirp::vector2f;

		auto get_speed() const -> float;

		static auto eq(const chirp::direction &dir1, const chirp::direction &dir2) -> bool;
	};
}
