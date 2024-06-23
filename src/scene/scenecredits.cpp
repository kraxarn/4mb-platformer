#include "scenecredits.hpp"

#include "colors.hpp"
#include "level/levelloader.hpp"
#include "physics/tiles.hpp"

#include <chirp/format.hpp>
#include <chirp/scenemanager.hpp>

scene_credits::scene_credits(const chirp::assets &assets)
	: scene(assets),
	assets(assets)
{
}

void scene_credits::load()
{
	fnt_title = assets.font("menu", size_title);
	fnt_subtitle = assets.font("submenu", size_title / 2);

	txt_title = append("txt_title",
		new chirp::text(fnt_title, "Thanks for playing!", {0, 0}, size_title, color::text));

	txt_subtitle = append("txt_subtitle",
		new chirp::text(fnt_subtitle, "", {0, 0}, size_title / 2, color::text));

	const auto music = assets.music("credits");

	const auto jukebox = append("jbx_main", new chirp::jukebox());
	jukebox->insert(music);
	jukebox->play();
}

void scene_credits::update(const float delta)
{
	scene::update(delta);

	// Title text
	const auto title_size = txt_title->measure().to<int>();
	txt_title->set_position({
		window().get_size().x() / 2 - title_size.x() / 2,
		window().get_size().y() / 2 - title_size.y(),
	});

	// Subtitle text
	const auto subtitle_size = txt_subtitle->measure().to<int>();
	txt_subtitle->set_position({
		window().get_size().x() / 2 - subtitle_size.x() / 2,
		window().get_size().y() / 2 + subtitle_size.y(),
	});

	// Go back to menu on enter
	if (keymap.is_pressed("enter"))
	{
		scenes().pop();
	}
}

auto scene_credits::get_total_coins() -> int
{
	auto coins = 0;
	auto index = 0;

	while (true)
	{
		if (!level_loader::is_valid(index))
		{
			break;
		}

		const auto *level = level_loader::get(assets, index++);
		for (const auto &tile: level->tiles())
		{
			if (tile.value == static_cast<char>(tile::coin))
			{
				coins++;
			}
		}
	}

	return coins;
}

void scene_credits::set_collected_coins(int value)
{
	auto total = get_total_coins();
	auto missed = total - value;

	txt_subtitle->set_text(missed == 0
		? "and you collected all coins! :)"
		: chirp::format("but you missed {} {}! :(",
			missed, missed == 1 ? "coin" : "coins"));
}
