#include "scenemenu.hpp"

scene_menu::scene_menu(const ce::assets &assets)
	: ce::scene(assets),
	fnt_menu(assets.font("font/menu.ttf", 52)),
	tex_arrow(assets.image("arrow.png"))
{
	std::array<std::string, text_count> labels = {
		"New game",
		"Load game",
		"Options",
		"Exit game",
	};

	// Temporary text placement to measure size
	texts.reserve(text_count);
	for (auto i = 0; i < text_count; i++)
	{
		texts.emplace_back(labels.at(i), 128, i * text_spacing,
			fnt_menu.font_size(), color::text);
	}

	// Place texts at center
	auto center = (GetScreenHeight() / 2) - (texts_height() / 2);
	for (auto i = 0; i < texts.size(); i++)
	{
		texts.at(i).set_y(center + (i * text_spacing));
	}

	// Arrow position
	tex_arrow.set_x(76);
}

void scene_menu::render()
{
	// Draw menu alternatives
	for (const auto &text : texts)
	{
		fnt_menu.draw_text(text);
	}

	// Update arrow position
	auto arrow_offset = std::abs(static_cast<float>(tex_arrow.get_x()) - 82.F);
	if (arrow_dir == direction::left)
	{
		tex_arrow.move(static_cast<int>(-0.5F - (arrow_offset / 10.F)), 0);
	}
	else
	{
		tex_arrow.move(0.5F + (arrow_offset / 10.F), 0);
	}

	if (tex_arrow.get_x() <= 64)
	{
		arrow_dir = direction::right;
	}
	else
	{
		arrow_dir = direction::left;
	}

	// Draw arrow
	tex_arrow.draw();
}

auto scene_menu::texts_height() -> int
{
	const auto &front = texts.front();
	const auto &back = texts.back();

	auto start = front.get_y();
	auto end = texts.back().get_y() + static_cast<int>(fnt_menu.text_size(back).y);
	return end - start;
}

void scene_menu::set_current(int value)
{
	current = value;
	const auto &text = texts.at(value);

	tex_arrow.set_y(text.get_y()
		+ static_cast<int>(fnt_menu.text_size(text).y / 2)
		- static_cast<int>(tex_arrow.get_height() / 2));
}
