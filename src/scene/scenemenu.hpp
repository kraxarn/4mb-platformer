#pragma once

#include "engine/scene.hpp"
#include "engine/text.hpp"
#include "engine/font.hpp"
#include "colors.hpp"

class scene_menu: public ce::scene
{
public:
	explicit scene_menu(const ce::assets &assets);
	void render() override;

private:
	ce::font font_menu;
	ce::font font_debug;

	static constexpr short text_count = 4;
	static constexpr short text_spacing = 48;

	std::vector<ce::text> texts;

	auto texts_height() -> int;
};
