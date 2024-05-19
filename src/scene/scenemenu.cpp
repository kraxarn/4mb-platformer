#include "scenemenu.hpp"

#include "colors.hpp"
#include "state.hpp"
#include "engine/clock.hpp"

#include <iomanip>
#include <sstream>

scene_menu::scene_menu(const chirp::assets &assets)
	: ce::scene(assets),
#ifndef NDEBUG
	txt_debug("-", {16, 16}, 20, chirp::color::white()),
#endif
	music(assets.music("menu")),
	fnt_menu(assets.font("menu", 52)),
	spr_arrow(assets.image("arrow")),
	spr_demo(assets.tileset("player"))
{
	std::array<std::string, text_count> labels = {
		"Start game",
		"Exit game",
	};

	// Temporary text placement to measure size
	texts.reserve(text_count);
	for (auto i = 0; i < text_count; i++)
	{
		texts.emplace_back(labels.at(i), chirp::vector2i(128, i * text_spacing),
			fnt_menu->font_size(), color::text);
	}

	// Place texts at center
	auto center = (GetScreenHeight() / 2) - (texts_height() / 2);
	for (auto i = 0; i < texts.size(); i++)
	{
		texts.at(i).set_position({
			texts.at(i).get_position().x(),
			center + i * text_spacing,
		});
	}

	// Arrow position
	spr_arrow.set_x(76);
	set_current(0);
	arrow_dir = direction::right;

	// Menu sprite
	reset_demo_position();
	spr_demo.set_scale(3.F);

	music->play();
}

void scene_menu::render()
{
	music->update();

	// Sprite demo
	spr_demo.move(-1.75F, 0);
	if (spr_demo.get_x() < -static_cast<float>(spr_demo.width()) * spr_demo.get_scale())
	{
		reset_demo_position();
	}
	spr_demo.draw();

	// Draw menu alternatives
	for (const auto &text : texts)
	{
		fnt_menu->draw_text(text);
	}

	// Check input
	if (keymap.is_pressed("up"))
	{
		set_current(current - 1);
	}
	else if (keymap.is_pressed("down"))
	{
		set_current(current + 1);
	}
	else if (keymap.is_pressed("enter"))
	{
		// Start game :)
		if (current == 0)
		{
			state::set(::scene::level, assets);
			auto *scene = dynamic_cast<scene_level *>(state::get().get());
			if (scene != nullptr)
			{
				scene->load(0);
			}
		}

		// Exit game :(
		if (current == 1)
		{
			ce::window::close();
			exit(0);
		}
	}

	// Update arrow position
	auto arrow_offset = std::abs(static_cast<float>(spr_arrow.get_x()) - 82.F);

	if (arrow_dir == direction::left)
	{
		spr_arrow.move(-0.5F - (arrow_offset / 10.F), 0);
	}
	else
	{
		spr_arrow.move(0.5F + (arrow_offset / 10.F), 0);
	}

	if (spr_arrow.get_x() <= 64)
	{
		arrow_dir = direction::right;
	}
	else if (spr_arrow.get_x() >= 82)
	{
		arrow_dir = direction::left;
	}

	// Draw arrow
	spr_arrow.draw();

	// Debug stuff
#ifndef NDEBUG
	std::stringstream stream;
	stream << "Debug Mode" << '\n'
		<< "Current: " << current << '\n'
		<< "FPS: " << ce::clock::fps() << '\n'
		<< "FrameTime: " << std::fixed << std::setprecision(2)
		<< (ce::clock::frame_time() * 1000.F);

	txt_debug.set_text(stream.str());
	txt_debug.draw();
#endif
}

auto scene_menu::texts_height() -> int
{
	const auto &front = texts.front();
	const auto &back = texts.back();

	const auto start = front.get_position().y();
	const auto end = texts.back().get_position().y() + static_cast<int>(fnt_menu->text_size(back).y());
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
	spr_arrow.set_y(static_cast<float>(text.get_position().y())
		+ (fnt_menu->text_size(text).y() / 2.F)
		- (static_cast<float>(spr_arrow.height()) / 2.F));
}

void scene_menu::reset_demo_position()
{
	auto screen_width = static_cast<float>(GetScreenWidth());
	auto sprite_width = static_cast<float>(spr_demo.width()) * spr_demo.get_scale();

	auto height = static_cast<float>(GetScreenHeight());
	auto min = static_cast<int>(height * 0.05F);
	auto max = static_cast<int>(height * 0.95F);

	spr_demo.set_x(screen_width + sprite_width);
	spr_demo.set_y(static_cast<float>(GetRandomValue(min, max)));
}
