#pragma once

#include "engine/window.hpp"

#include <chirp/assets.hpp>

namespace entity
{
	class level_title
	{
	public:
		explicit level_title(const chirp::assets &assets);

		void update(float delta);
		void set_level(const chirp::level &level);

	private:
		static constexpr int font_size = 42;
		static constexpr float timer_start = 2.F;

		int speed = 0;
		float timer = timer_start;
		chirp::vector2i text_size;

		chirp::asset<chirp::font> font;
		chirp::text text;
	};
}
