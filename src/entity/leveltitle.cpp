#include "leveltitle.hpp"

entity::level_title::level_title(const ce::assets &assets)
	: font(assets.font("menu", font_size)),
	text("Level 1", {0, 0}, font_size, color::text)
{
}

void entity::level_title::update()
{
	if (text.get_position().y() < -text_size.y())
	{
		return;
	}

	font.draw_text(text);
	if (timer > 0)
	{
		timer--;
		return;
	}

	text.set_position({
		text.get_position().x(),
		text.get_position().y() - speed++,
	});
}

void entity::level_title::set_level(const chirp::level &level)
{
	text.set_text(level.name());

	text_size = font.text_size(text).to<int>();

	text.set_position({
		ce::window::size().x() / 2 - text_size.x() / 2,
		text_size.y(),
	});

	timer = timer_start;
}
