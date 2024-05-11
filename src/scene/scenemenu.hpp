#pragma once

#include "engine/animatedsprite.hpp"
#include "engine/input.hpp"
#include "engine/scene.hpp"
#include "engine/sprite.hpp"
#include "enum/direction.hpp"

#include <chirp/font.hpp>
#include <chirp/text.hpp>

class scene_menu: public ce::scene
{
public:
	explicit scene_menu(const ce::assets &assets);
	void render() override;

private:
	static constexpr short text_count = 2;
	static constexpr short text_spacing = 48;

	chirp::music music;

#ifndef NDEBUG
	chirp::text txt_debug;
#endif

	ce::sprite spr_arrow;
	direction arrow_dir;
	int current = 0;

	ce::animated_sprite spr_demo;

	chirp::font fnt_menu;
	std::vector<chirp::text> texts;

	ce::input input;

	auto texts_height() -> int;

	void set_current(int value);
	void reset_demo_position();
};
