#include "scenecredits.hpp"
#include "level/levelloader.hpp"

#include <chirp/format.hpp>

scene_credits::scene_credits(const ce::assets &assets)
	: ce::scene(assets),
	fnt_title(assets.font("menu", size_title)),
	fnt_subtitle(assets.font("submenu", size_title / 2)),
	txt_title("Thanks for playing!", {0, 0}, size_title, color::text),
	txt_subtitle("", {0, 0}, size_title / 2, color::text),
	music(assets.music("credits"))
{
	music.play();
}

void scene_credits::render()
{
	music.update();

	// Title text
	const auto title_size = fnt_title.text_size(txt_title).to<int>();
	txt_title.set_position({
		ce::window::size().x() / 2 - title_size.x() / 2,
		ce::window::size().y() / 2 - title_size.y(),
	});
	fnt_title.draw_text(txt_title);

	// Subtitle text
	const auto subtitle_size = fnt_subtitle.text_size(txt_subtitle).to<int>();
	txt_subtitle.set_position({
		ce::window::size().x() / 2 - subtitle_size.x() / 2,
		ce::window::size().y() / 2 + subtitle_size.y(),
	});
	fnt_subtitle.draw_text(txt_subtitle);

	// Go back to menu on enter
	if (input.is_pressed(ce::key::enter))
	{
		state::set(::scene::menu, assets);
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

		ce::iterate_map_all<char>(level_loader::get(assets, index++)->map(),
			[&coins](int /*x*/, int /*y*/, char value)
			{
				if (value == static_cast<char>(tile::coin))
				{
					coins++;
				}
			});
	}

	return coins;
}

void scene_credits::set_collected_coins(int value)
{
	auto total = get_total_coins();
	auto missed = total - value;

	txt_subtitle.set_text(missed == 0
		? "and you collected all coins! :)"
		: chirp::format("but you missed {} {}! :(",
			missed, missed == 1 ? "coin" : "coins"));
}
