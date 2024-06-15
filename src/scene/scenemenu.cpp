#include "scenemenu.hpp"

#include "colors.hpp"
#include "scene/scenelevel.hpp"

#include <chirp/clock.hpp>
#include <chirp/colors.hpp>
#include <chirp/os.hpp>
#include <chirp/random.hpp>
#include <chirp/scenemanager.hpp>

#include <iomanip>
#include <sstream>

scene_menu::scene_menu(const chirp::assets &assets)
	: scene(assets),
	txt_debug("-", {16, 16}, 20, chirp::colors::white()),
	music(assets.music("menu")),
	fnt_menu(assets.font("menu", 52)),
	spr_arrow(assets.image("arrow")),
	spr_demo(assets.tileset("player")),
	assets(assets)
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
	const auto window_size = window().get_size();
	const auto center = (window_size.y() / 2) - (texts_height() / 2);
	for (auto i = 0; i < texts.size(); i++)
	{
		texts.at(i).set_position({
			texts.at(i).get_position().x(),
			center + i * text_spacing,
		});
	}

	// Arrow position
	spr_arrow.set_position({76, spr_arrow.get_position().y()});
	set_current(0);
	arrow_dir = chirp::direction::right;

	// Menu sprite
	reset_demo_position();
	spr_demo.set_scale(3.F);

	music->play();
}

void scene_menu::update(const float delta)
{
	scene::update(delta);

	music->update();

	spr_demo.set_position(spr_demo.get_position() + chirp::vector2f(-1.75F, 0.F));
	if (spr_demo.get_position().x() < -spr_demo.get_shape().width() * spr_demo.get_scale())
	{
		reset_demo_position();
	}

	spr_demo.update(delta);

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
			scenes().push<scene_level>();
			if (const auto scene = std::dynamic_pointer_cast<scene_level>(scenes().peek()))
			{
				scene->load(0);
			}
		}

		// Exit game :(
		if (current == 1)
		{
			scenes().pop();
		}
	}

	// Update arrow position
	const auto arrow_offset = std::abs(spr_arrow.get_position().x() - 82.F);

	if (arrow_dir == chirp::direction::left)
	{
		spr_arrow.set_position({
			spr_arrow.get_position().x() - 0.5F - arrow_offset / 10.F,
			spr_arrow.get_position().y(),
		});
	}
	else
	{
		spr_arrow.set_position({
			spr_arrow.get_position().x() + 0.5F + arrow_offset / 10.F,
			spr_arrow.get_position().y(),
		});
	}

	if (spr_arrow.get_position().x() <= 64)
	{
		arrow_dir = chirp::direction::right;
	}
	else if (spr_arrow.get_position().x() >= 82)
	{
		arrow_dir = chirp::direction::left;
	}

	// Debug stuff
	if (chirp::os::is_debug())
	{
		std::stringstream stream;

		stream << "Debug Mode" << '\n'
			<< "Current: " << current << '\n'
			<< "FPS: " << chirp::clock::fps() << '\n'
			<< "Delta: " << std::fixed << std::setprecision(2) << delta * 1000.F;

		txt_debug.set_text(stream.str());
	}
}

void scene_menu::draw()
{
	scene::draw();

	spr_demo.draw();

	// Draw menu alternatives
	for (const auto &text : texts)
	{
		fnt_menu->draw_text(text);
	}

	// Draw arrow
	spr_arrow.draw();

	// Debug stuff
	if (chirp::os::is_debug())
	{
		txt_debug.draw();
	}
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

	spr_arrow.set_position({
		spr_arrow.get_position().x(),
		static_cast<float>(text.get_position().y())
		+ fnt_menu->text_size(text).y() / 2.F
		- static_cast<float>(spr_arrow.get_size().y()) / 2.F
	});
}

void scene_menu::reset_demo_position()
{
	const auto window_size = window().get_size();
	const auto screen_width = static_cast<float>(window_size.x());
	auto sprite_width = spr_demo.get_shape().width() * spr_demo.get_scale();

	const auto height = static_cast<float>(window_size.y());
	auto min = static_cast<int>(height * 0.05F);
	auto max = static_cast<int>(height * 0.95F);

	spr_demo.set_position(chirp::vector2f{
		screen_width + sprite_width,
		static_cast<float>(chirp::random::get(min, max)),
	});
}
