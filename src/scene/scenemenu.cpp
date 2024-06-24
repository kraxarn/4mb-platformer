#include "scenemenu.hpp"

#include "colors.hpp"
#include "scene/scenelevel.hpp"

#include <chirp/clock.hpp>
#include <chirp/colors.hpp>
#include <chirp/entitycontainer.hpp>
#include <chirp/format.hpp>
#include <chirp/os.hpp>
#include <chirp/random.hpp>
#include <chirp/scenemanager.hpp>

#include <iomanip>
#include <sstream>

void scene_menu::load()
{
	std::array<std::string, text_count> labels = {
		"Start game",
		"Exit game",
	};

	jbx_music = append("jbx_music", new chirp::jukebox());
	const auto music = assets().music("menu");
	jbx_music->insert(music);

	if (!chirp::os::is_debug())
	{
		jbx_music->play();
	}

	spr_demo = append("spr_demo",
		new chirp::animated_sprite(assets().tileset("player")));

	if (chirp::os::is_debug())
	{
		txt_debug = append("txt_debug", new chirp::text("...",
			chirp::vector2i(16, 16), 20, chirp::colors::white()));
	}

	const auto font = assets().font("menu", 52);

	// Temporary text placement to measure size
	texts.reserve(text_count);
	for (auto i = 0; i < text_count; i++)
	{
		const auto text = append(chirp::format("txt_menu_{}", i),
			new chirp::text(font, labels.at(i), chirp::vector2i(128, i * text_spacing),
				font->font_size(), color::text));

		texts.push_back(text);
	}

	// Place texts at center
	const auto window_size = window().get_size();
	const auto center = (window_size.y() / 2) - (texts_height() / 2);
	for (auto i = 0; i < texts.size(); i++)
	{
		texts.at(i)->set_position({
			texts.at(i)->get_position().x(),
			center + i * text_spacing,
		});
	}

	spr_arrow = append("spr_arrow",
		new chirp::sprite(assets().image("arrow")));

	// Arrow position
	spr_arrow->set_position({76, spr_arrow->get_position().y()});
	set_current(0);
	arrow_dir = chirp::direction::right;

	// Menu sprite
	reset_demo_position();
	spr_demo->set_scale(3.F);
}

void scene_menu::update(const float delta)
{
	scene::update(delta);

	spr_demo->set_position(spr_demo->get_position() + chirp::vector2f(-1.75F, 0.F));
	if (spr_demo->get_position().x() < -spr_demo->get_shape().width() * spr_demo->get_scale())
	{
		reset_demo_position();
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
			scenes().push(new scene_level());
			if (const auto scene = std::dynamic_pointer_cast<scene_level>(scenes().peek()))
			{
				scene->load(0);
			}
		}

		// Exit game :(
		if (current == 1)
		{
			scenes().queue_pop();
		}
	}

	// Update arrow position
	const auto arrow_offset = std::abs(spr_arrow->get_position().x() - 82.F);

	if (arrow_dir == chirp::direction::left)
	{
		spr_arrow->set_position({
			spr_arrow->get_position().x() - 0.5F - arrow_offset / 10.F,
			spr_arrow->get_position().y(),
		});
	}
	else
	{
		spr_arrow->set_position({
			spr_arrow->get_position().x() + 0.5F + arrow_offset / 10.F,
			spr_arrow->get_position().y(),
		});
	}

	if (spr_arrow->get_position().x() <= 64)
	{
		arrow_dir = chirp::direction::right;
	}
	else if (spr_arrow->get_position().x() >= 82)
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
			<< "Delta: " << std::fixed << std::setprecision(2) << delta * 1000.F << "\n\n"
			<< "Entities  (" << entities().size() << "):";

		for (const auto &name: entity_keys())
		{
			stream << '\n' << name;
		}

		txt_debug->set_text(stream.str());
	}
}

auto scene_menu::texts_height() -> int
{
	const auto &front = texts.front();
	const auto &back = texts.back();

	const auto start = front->get_position().y();
	const auto end = back->get_position().y() + static_cast<int>(back->measure().y());
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

	spr_arrow->set_position({
		spr_arrow->get_position().x(),
		static_cast<float>(text->get_position().y())
		+ text->measure().y() / 2.F
		- static_cast<float>(spr_arrow->get_size().y()) / 2.F
	});
}

void scene_menu::reset_demo_position()
{
	const auto window_size = window().get_size();
	const auto screen_width = static_cast<float>(window_size.x());
	auto sprite_width = spr_demo->get_shape().width() * spr_demo->get_scale();

	const auto height = static_cast<float>(window_size.y());
	auto min = static_cast<int>(height * 0.05F);
	auto max = static_cast<int>(height * 0.95F);

	spr_demo->set_position(chirp::vector2f{
		screen_width + sprite_width,
		static_cast<float>(chirp::random::get(min, max)),
	});
}
