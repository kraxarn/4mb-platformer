#include "pause.hpp"

entity::pause::pause(const ce::assets &assets)
	: fnt_title(assets.font("menu", title_size)),
	txt_title("Paused", {0, 0}, title_size, color::text)
{
}

auto entity::pause::get_paused() const -> bool
{
	return paused;
}

void entity::pause::set_paused(bool value)
{
	paused = value;
}

void entity::pause::update()
{
	if (!paused)
	{
		return;
	}

	const auto window_size = ce::window::size();
	DrawRectangle(0, 0, window_size.x(), window_size.y(), {
		0x0, 0x0, 0x0, 0x7f,
	});

	const auto text_size = fnt_title.text_size(txt_title).to<int>();
	txt_title.set_position({
		window_size.x() / 2 - text_size.x() / 2,
		window_size.y() / 2 - text_size.y() / 2,
	});

	fnt_title.draw_text(txt_title);
}
