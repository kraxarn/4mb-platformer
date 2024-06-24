#pragma once

#include "keymap.hpp"

#include <chirp/asset.hpp>
#include <chirp/assets.hpp>
#include <chirp/entity.hpp>
#include <chirp/font.hpp>
#include <chirp/text.hpp>
#include <chirp/window.hpp>

namespace entity
{
	class pause: public chirp::entity
	{
	public:
		explicit pause(const chirp::assets &assets, const chirp::window &window);

		void update(const chirp::scene &scene, float delta) override;
		void draw() const override;

		auto get_paused() const -> bool;
		void set_paused(bool value);

	private:
		static constexpr auto title_size = 42;
		static constexpr auto menu_size = 32;

		bool paused = false;
		int current_position = 0;

		chirp::asset<chirp::font> fnt_title;
		chirp::asset<chirp::font> fnt_menu;

		chirp::text txt_title;
		chirp::text txt_menu;

		const chirp::window &window;
		::keymap keymap;

		void update_position(int mod);
	};
}
