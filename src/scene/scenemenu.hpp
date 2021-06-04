#pragma once

#include "engine/scene.hpp"
#include "engine/text.hpp"
#include "engine/font.hpp"
#include "engine/texture.hpp"
#include "engine/clock.hpp"
#include "engine/input.hpp"
#include "engine/window.hpp"
#include "engine/animatedsprite.hpp"
#include "engine/sprite.hpp"
#include "colors.hpp"
#include "enum/direction.hpp"

#include <cmath>
#include <iomanip>

class scene_menu: public ce::scene
{
public:
	explicit scene_menu(const ce::assets &assets);
	void render() override;

private:
	static constexpr short text_count = 4;
	static constexpr short text_spacing = 48;

	ce::music music;

	ce::font fnt_debug;
	ce::text txt_debug;

	ce::sprite spr_arrow;
	direction arrow_dir;
	int current = 0;

	ce::animated_sprite spr_demo;

	ce::font fnt_menu;
	std::vector<ce::text> texts;

	ce::input input;

	auto texts_height() -> int;

	void set_current(int value);
};
