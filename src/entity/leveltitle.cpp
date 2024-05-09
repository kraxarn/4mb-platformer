#include "leveltitle.hpp"

entity::level_title::level_title(const ce::assets &assets)
	: font(assets.font("menu", font_size)),
	text("Level 1", 0, 0, font_size, color::text)
{
}

void entity::level_title::update()
{
	if (text.get_y() < -text_size.y)
	{
		return;
	}

	font.draw_text(text);
	if (timer > 0)
	{
		timer--;
		return;
	}

	text.set_y(text.get_y() - speed++);
}

void entity::level_title::set_level(const ce::level &level)
{
	text.set_text(level.name());

	text_size = ce::vector2i(font.text_size(text));
	text.set_x(ce::window::size().x / 2 - text_size.x / 2);
	text.set_y(text_size.y);

	timer = timer_start;
}
