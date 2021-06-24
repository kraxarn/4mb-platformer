#include "pause.hpp"

entity::pause::pause(const ce::assets &assets)
	: fnt_title(assets.font("menu.ttf", title_size)),
	txt_title("Paused", 0, 0, title_size, color::text)
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

	auto text_size = ce::vector2i(fnt_title.text_size(txt_title));
	txt_title.set_x(ce::window::size().x / 2 - text_size.x / 2);
	txt_title.set_y(ce::window::size().y / 2 - text_size.y);
	fnt_title.draw_text(txt_title);
}
