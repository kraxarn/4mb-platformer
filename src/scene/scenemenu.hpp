#pragma once

#include "keymap.hpp"

#include <chirp/animatedsprite.hpp>
#include <chirp/direction.hpp>
#include <chirp/font.hpp>
#include <chirp/scene.hpp>
#include <chirp/sprite.hpp>
#include <chirp/text.hpp>

class scene_menu: public chirp::scene
{
public:
	explicit scene_menu(const chirp::assets &assets);

	void update(float delta) override;

	void draw() override;

private:
	static constexpr short text_count = 2;
	static constexpr short text_spacing = 48;

	chirp::sprite spr_arrow;
	chirp::direction arrow_dir;
	int current = 0;

	chirp::animated_sprite spr_demo;

	chirp::asset<chirp::font> fnt_menu;
	std::vector<chirp::text> texts;

	::keymap keymap;
	const chirp::assets &assets;

	auto texts_height() -> int;

	void set_current(int value);
	void reset_demo_position();
};
