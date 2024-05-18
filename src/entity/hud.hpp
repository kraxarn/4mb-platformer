#pragma once

#include "engine/level.hpp"
#include "engine/window.hpp"
#include "entity/state.hpp"

#include <chirp/assets.hpp>

namespace entity
{
	class hud
	{
	public:
		explicit hud(const chirp::assets &assets);

		void draw(ce::level &level);

		auto get_gem_count() const -> int;
		auto get_coin_count() const -> int;

		/** Increment coins by one */
		void add_coin();
		/** Increment gems by one */
		void add_gem();
		/** Reset elements for level switch */
		void reset();

		/** Kill player :( */
		void kill();
		/** Player respawned :) */
		void respawn();
		/** Player is dead */
		auto is_dead() const -> bool;

		auto get_player_speed_modifier() const -> float;
		void set_player_speed_modifier(float value);

	private:
		/** Font size for all HUD elements */
		static constexpr int font_size = 30;

		/** Offset from top right corner to draw HUD */
		static constexpr float offset = 12.F;

		/** Spacing between each element */
		static constexpr int spacing = 6;

		/** Scale of all images in HUD */
		static constexpr float scale = 2.F;

		entity::state state;

		chirp::asset<chirp::font> fnt_hud;
		chirp::text txt_gems;
		chirp::text txt_coins;

		chirp::asset<chirp::tileset> ts_hud;
		chirp::vector2f pos_gems;
		chirp::vector2f pos_coins;

		chirp::asset<chirp::sound> snd_coin;
		chirp::asset<chirp::sound> snd_gem;
		chirp::asset<chirp::sound> snd_fall;

		float player_speed_modifier = 1.F;

		void update(ce::level &level);
	};
}
