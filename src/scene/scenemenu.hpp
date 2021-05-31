#pragma once

#include "engine/scene.hpp"
#include "engine/text.hpp"
#include "engine/font.hpp"
#include "engine/texture.hpp"
#include "colors.hpp"
#include "enum/direction.hpp"

#include <cmath>

class scene_menu: public ce::scene
{
public:
	explicit scene_menu(const ce::assets &assets);
	void render() override;

private:
	ce::font fnt_menu;

	ce::texture tex_arrow;
	direction arrow_dir = direction::left;

	static constexpr short text_count = 4;
	static constexpr short text_spacing = 48;

	int current = 0;

	std::vector<ce::text> texts;

	auto texts_height() -> int;
	void set_current(int value);
};
