#pragma once

#include <chirp/assets.hpp>
#include <chirp/window.hpp>

namespace entity
{
	class pause
	{
	public:
		explicit pause(const chirp::assets &assets, const chirp::window &window);

		void update();

		void draw() const;

		auto get_paused() const -> bool;
		void set_paused(bool value);

	private:
		static constexpr int title_size = 42;

		bool paused = false;

		chirp::asset<chirp::font> fnt_title;
		chirp::text txt_title;
		const chirp::window &window;
	};
}
