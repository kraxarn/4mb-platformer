#include "leveltitle.hpp"
#include "colors.hpp"

entity::level_title::level_title(const chirp::assets &assets, const chirp::window &window)
	: font(assets.font("menu", font_size)),
	text("Level 1", {0, 0}, font_size, color::text),
	window(window)
{
}

void entity::level_title::update(const float delta)
{
	if (!is_visible())
	{
		return;
	}

	if (timer > 0)
	{
		timer -= delta;
		return;
	}

	speed += delta * (60.F / 1.F);

	text.set_position({
		text.get_position().x(),
		text.get_position().y() - static_cast<int>(speed),
	});
}

void entity::level_title::draw() const
{
	if (!is_visible())
	{
		return;
	}

	font->draw_text(text);
}

auto entity::level_title::is_visible() const -> bool
{
	return text.get_position().y() > -text_size.y();
}

void entity::level_title::set_level(const chirp::level &level)
{
	text.set_text(level.name());

	text_size = font->text_size(text).to<int>();

	text.set_position({
		window.get_size().x() / 2 - text_size.x() / 2,
		text_size.y(),
	});

	timer = timer_start;
}
