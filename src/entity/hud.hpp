#pragma once

#include "engine/assets.hpp"
#include "engine/window.hpp"
#include "engine/format.hpp"
#include "colors.hpp"
#include "physics/tiles.hpp"

namespace entity
{
	class hud
	{
	public:
		explicit hud(const ce::assets &assets);

		void draw();

	private:
		/** Font size for all HUD elements */
		static constexpr int font_size = 30;

		/** Offset from top right corner to draw HUD */
		static constexpr float offset = 12.F;

		/** Spacing between each element */
		static constexpr int spacing = 6;

		/** Width to reserve for text */
		static constexpr int text_width = font_size;

		/** Scale of all images in HUD */
		static constexpr float scale = 2.F;

		/** Coins total */
		int coins = 0;

		/** Gems collected for current level */
		int gems = 0;

		/** Total gems in current level */
		int total_gems = 0;

		asset::font fnt_hud;
		ce::text txt_gems;
		ce::text txt_coins;

		asset::tileset ts_hud;
		ce::vector2f pos_gems;
		ce::vector2f pos_coins;

		void update();
	};
}
