#include "scenecredits.hpp"

scene_credits::scene_credits(const ce::assets &assets)
	: ce::scene(assets),
	fnt_title(assets.font("menu.ttf", size_title)),
	txt_title("Thanks for playing!", 0, 0, size_title, color::text),
	music(assets.music("credits.xm"))
{
	music.play();
}

void scene_credits::render()
{
	music.update();

	// Title text
	auto title_size = ce::vector2i(fnt_title.text_size(txt_title));
	txt_title.set_x(ce::window::size().x / 2 - title_size.x / 2);
	txt_title.set_y(ce::window::size().y / 2 - title_size.y / 2);

	fnt_title.draw_text(txt_title);
}
