#pragma once

#include "engine/assets.hpp"
#include "engine/window.hpp"
#include "engine/format.hpp"
#include "engine/level.hpp"
#include "colors.hpp"
#include "physics/tiles.hpp"
#include "entity/state.hpp"

namespace entity
{
	class hud
	{
	public:
		explicit hud(const ce::assets &assets);

		void draw(ce::level &level);

		auto get_gem_count() const -> int;

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

		asset::font fnt_hud;
		ce::text txt_gems;
		ce::text txt_coins;

		asset::tileset ts_hud;
		ce::vector2f pos_gems;
		ce::vector2f pos_coins;

		asset::sound snd_coin;
		asset::sound snd_gem;
		asset::sound snd_fall;

		void update(ce::level &level);
	};
}
