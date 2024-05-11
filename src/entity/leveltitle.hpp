#pragma once

#include "engine/assets.hpp"
#include "engine/window.hpp"
#include "colors.hpp"

namespace entity
{
	class level_title
	{
	public:
		explicit level_title(const ce::assets &assets);

		void update();
		void set_level(const ce::level &level);

	private:
		static constexpr int font_size = 42;
		static constexpr int timer_start = 60 * 2;

		int speed = 0;
		int timer = timer_start;
		chirp::vector2i text_size;

		asset::font font;
		ce::text text;
	};
}
