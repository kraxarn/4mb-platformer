#pragma once

#include <chirp/assets.hpp>
#include <chirp/text.hpp>
#include <chirp/window.hpp>

namespace entity
{
	class level_title
	{
	public:
		explicit level_title(const chirp::assets &assets, const chirp::window &window);

		void update(float delta);

		void draw() const;

		void set_level(const chirp::level &level);

	private:
		static constexpr int font_size = 42;
		static constexpr float timer_start = 2.F;

		float speed = 0;
		float timer = timer_start;
		chirp::vector2i text_size;

		chirp::asset<chirp::font> font;
		chirp::text text;
		const chirp::window &window;

		auto is_visible() const -> bool;
	};
}
