#pragma once

#include "engine/assets.hpp"
#include "engine/window.hpp"
#include "colors.hpp"

namespace entity
{
	class pause
	{
	public:
		explicit pause(const ce::assets &assets);

		void update();

		auto get_paused() const -> bool;
		void set_paused(bool value);

	private:
		static constexpr int title_size = 24;

		bool paused = false;

		asset::font fnt_title;
		ce::text txt_title;
	};
}
