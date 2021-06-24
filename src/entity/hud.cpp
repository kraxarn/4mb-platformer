#include "entity/hud.hpp"

entity::hud::hud(const ce::assets &assets)
	: fnt_hud(assets.font("submenu.ttf", font_size)),
	txt_gems("0/0", 0, 0, font_size, color::text),
	txt_coins("0", 0, 0, font_size, color::text),
	ts_hud(assets.tileset("items.png")),
	snd_coin(assets.sound("coin.wav")),
	snd_gem(assets.sound("gem.wav")),
	snd_fall(assets.sound("fall.wav"))
{
	/*
	 * /-----------------------tr
	 * | txt_gem   | img_gem   |
	 * | txt_coins | img_coins |
	 * \-----------------------/
	 */

	ce::vector2f top_right{
		ce::window::size().to<float>().x - offset,
		offset,
	};

	auto hud_height = static_cast<float>(ts_hud.get_size());
	auto font_offset = (ts_hud.get_size()
		- ce::vector2i(fnt_hud.text_size(txt_gems)).y) / 4;

	pos_gems.x = top_right.x - offset - hud_height * scale;
	pos_gems.y = offset;

	pos_coins.x = pos_gems.x;
	pos_coins.y = pos_gems.y + hud_height * scale + spacing;

	// Coin
	txt_gems.set_x(pos_gems.to<int>().x);
	txt_gems.set_y(pos_gems.to<int>().y - font_offset);
	// gem
	txt_coins.set_x(pos_coins.to<int>().x);
	txt_coins.set_y(pos_coins.to<int>().y - font_offset);
}

void entity::hud::draw(ce::level &level)
{
	update(level);

	// Text positions
	txt_gems.set_x(pos_gems.to<int>().x
		- ce::vector2i(fnt_hud.text_size(txt_gems)).x);
	txt_coins.set_x(pos_coins.to<int>().x
		- ce::vector2i(fnt_hud.text_size(txt_coins)).x);

	// Text
	if (level.get_total_gem_count() > 0)
	{
		fnt_hud.draw_text(txt_gems);
	}
	fnt_hud.draw_text(txt_coins);

	// Coin
	ts_hud.draw(pos_coins.x, pos_coins.y,
		static_cast<int>(tile::coin) % static_cast<int>(tile::spawn),
		0.F, scale);
	// Gem
	if (level.get_total_gem_count() > 0)
	{
		ts_hud.draw(pos_gems.x, pos_gems.y,
			static_cast<int>(tile::gem) % static_cast<int>(tile::spawn),
			0.F, scale);
	}
}

void entity::hud::update(ce::level &level)
{
	txt_gems.set_text(ce::fmt::format("{}/{}",
		state.get_gems(), level.get_total_gem_count()));
	txt_coins.set_text(std::to_string(state.get_coins()));
}

auto entity::hud::get_gem_count() const -> int
{
	return state.get_gems();
}

void entity::hud::add_coin()
{
	snd_coin.play();
	state.add_coins(1);
}

void entity::hud::add_gem()
{
	snd_gem.play();
	state.add_gems(1);
}

void entity::hud::reset()
{
	state.set_gems(0);
}

void entity::hud::kill()
{
	snd_fall.play();
	state.set_dead(true);
}

void entity::hud::respawn()
{
	state.set_dead(false);
}

auto entity::hud::is_dead() const -> bool
{
	return state.get_dead();
}
