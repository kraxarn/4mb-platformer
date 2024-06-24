#include "pause.hpp"
#include "colors.hpp"

#include <chirp/format.hpp>
#include <chirp/rectangle.hpp>
#include <chirp/scene.hpp>
#include <chirp/scenemanager.hpp>
#include <chirp/window.hpp>

#include "map.hpp"
#include "player.hpp"

entity::pause::pause(const chirp::assets &assets, const chirp::window &window)
	: fnt_title(assets.font("menu", title_size)),
	fnt_menu(assets.font("submenu", menu_size)),
	txt_title(fnt_title, "Paused", {0, 0}, title_size, color::text),
	txt_menu(fnt_menu, "", {0, 0}, menu_size, color::text),
	window(window)
{
	update_position(0);
}

auto entity::pause::get_paused() const -> bool
{
	return paused;
}

void entity::pause::set_paused(bool value)
{
	paused = value;
	update_position(-current_position);
}

void entity::pause::update(const chirp::scene &scene, const float /*delta*/)
{
	if (!paused)
	{
		return;
	}

	const auto window_size = window.get_size();

	const auto text_size = txt_title.measure().to<int>();
	txt_title.set_position({
		window_size.x() / 2 - text_size.x() / 2,
		window_size.y() / 2 - text_size.y() / 2,
	});

	txt_menu.set_position({
		txt_title.get_position().x(),
		txt_title.get_position().y() + text_size.y() + 16,
	});

	if (keymap.is_pressed("up"))
	{
		update_position(-1);
	}
	else if (keymap.is_pressed("down"))
	{
		update_position(1);
	}
	else if (keymap.is_pressed("enter"))
	{
		if (current_position == 0)
		{
			// Resume
			set_paused(false);
		}
		else if (current_position == 1)
		{
			// Restart level
			const auto &player = scene.find<::entity::player>("cam_main/spr_player");
			const auto &map = scene.find<::entity::map>("cam_main/map_main");

			if (player && map)
			{
				const auto safe_spawn = map->get_level()->get_safe_spawn();
				player->set_velocity({0, 0});
				player->set_position(safe_spawn);
			}

			set_paused(false);
		}
		else if (current_position == 2)
		{
			// Back to menu
			scene.scenes().queue_pop();
		}
	}
}

void entity::pause::draw() const
{
	if (!paused)
	{
		return;
	}

	const auto window_size = window.get_size();
	const chirp::rectangle<int> background{
		0, 0,
		window_size.x(), window_size.y(),
	};

	chirp::draw_filled(background, {0x0, 0x0, 0x0, 0x7f});

	txt_title.draw();
	txt_menu.draw();
}

void entity::pause::update_position(const int mod)
{
	current_position += mod;

	constexpr auto min = 0;
	constexpr auto max = 2;

	if (current_position < min)
	{
		current_position = max;
	}
	else if (current_position > max)
	{
		current_position = min;
	}

	const auto text = chirp::format("{}Resume\n{}Restart level\n{}Back to menu",
		current_position == 0 ? "> " : "",
		current_position == 1 ? "> " : "",
		current_position == 2 ? "> " : "");

	txt_menu.set_text(text);
}
