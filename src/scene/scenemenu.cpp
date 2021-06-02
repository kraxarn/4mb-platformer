#include "scenemenu.hpp"

scene_menu::scene_menu(const ce::assets &assets)
	: ce::scene(assets),
	music(assets.music("menu.xm")),
	fnt_menu(assets.font("menu.ttf", 52)),
	fnt_debug(assets.font("debug.ttf", 22)),
	tex_arrow(assets.image("arrow.png")),
	txt_debug("-", 16, 16, fnt_debug.font_size(), WHITE),
	spr_demo(assets.tileset("player.png"))
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
	set_current(0);
	arrow_dir = direction::right;

	// Menu sprite
	spr_demo.set_pos(static_cast<float>(GetScreenWidth()) * 0.7F,
		static_cast<float>(GetScreenHeight()) * 0.6F);
	spr_demo.set_scale(3.F);

	music.play();
}

void scene_menu::render()
{
	music.update();

	// Sprite demo
	spr_demo.move(-1.F, 0);
	if (spr_demo.x() < -100)
	{
		spr_demo.set_pos(static_cast<float>(GetScreenWidth()) * 1.F,
			static_cast<float>(GetScreenHeight()) * 0.6F);
	}
	spr_demo.draw();

	// Draw menu alternatives
	for (const auto &text : texts)
	{
		fnt_menu.draw_text(text);
	}

	// Check input
	if (input.is_pressed(ce::key::up))
	{
		set_current(current - 1);
	}
	else if (input.is_pressed(ce::key::down))
	{
		set_current(current + 1);
	}
	else if (input.is_pressed(ce::key::enter))
	{
		switch (current)
		{
			// Exit game
			case 3:
				ce::window::close();
				exit(0);
		}
	}

	// Update arrow position
	auto arrow_offset = std::abs(static_cast<float>(tex_arrow.get_x()) - 82.F);

	if (arrow_dir == direction::left)
	{
		tex_arrow.move(-0.5F - (arrow_offset / 10.F), 0);
	}
	else
	{
		tex_arrow.move(0.5F + (arrow_offset / 10.F), 0);
	}

	if (tex_arrow.get_x() <= 64)
	{
		arrow_dir = direction::right;
	}
	else if (tex_arrow.get_x() >= 82)
	{
		arrow_dir = direction::left;
	}

	// Draw arrow
	tex_arrow.draw();

	// Debug stuff
	txt_debug.set_text(fmt::format("Current:\t{}\n"
								   "FPS:\t{}\n"
								   "FrameTime:\t{:.0}\n",
		current, ce::clock::fps(), ce::clock::frame_time() * 1000.F,
		tex_arrow.get_x(), tex_arrow.get_y(), arrow_offset));
	fnt_debug.draw_text(txt_debug);
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
	if (current < 0)
	{
		current = static_cast<int>(texts.size() - 1);
	}
	else if (current >= texts.size())
	{
		current = 0;
	}

	const auto &text = texts.at(current);
	tex_arrow.set_y(static_cast<float>(text.get_y())
		+ (fnt_menu.text_size(text).y / 2.F)
		- (static_cast<float>(tex_arrow.get_height()) / 2.F));
}
