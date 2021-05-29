#include "scenemenu.hpp"

scene_menu::scene_menu(const ce::assets &assets)
	: ce::scene(assets),
	font_menu(assets.font("font/menu.ttf", 52)),
	font_debug(assets.font("font/debug.ttf", 12))
{
	std::array<std::string, text_count> labels = {
		"New game",
		"Load game",
		"Options",
		"Exit game",
	};

	texts.reserve(text_count);
	for (auto i = 0; i < text_count; i++)
	{
		texts.emplace_back(labels.at(i), 128, i * text_spacing,
			font_menu.font_size(), color::text);
	}

	auto center = (GetScreenHeight() / 2) - (texts_height() / 2);
	for (auto i = 0; i < texts.size(); i++)
	{
		texts.at(i).set_y(center + (i * text_spacing));
	}
}

void scene_menu::render()
{
	for (const auto &text : texts)
	{
		font_menu.draw_text(text);
	}
}

auto scene_menu::texts_height() -> int
{
	const auto &front = texts.front();
	const auto &back = texts.back();

	auto start = front.get_y();
	auto end = texts.back().get_y() + static_cast<int>(font_menu.text_size(back).y);
	return end - start;
}
