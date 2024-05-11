#include "entity/hud.hpp"

entity::hud::hud(const ce::assets &assets)
	: fnt_hud(assets.font("submenu", font_size)),
	txt_gems("0/0", 0, 0, font_size, color::text),
	txt_coins("0", 0, 0, font_size, color::text),
	ts_hud(assets.tileset("items")),
	snd_coin(assets.sound("coin")),
	snd_gem(assets.sound("gem")),
	snd_fall(assets.sound("fall"))
{
	/*
	 * /-----------------------tr
	 * | txt_gem   | img_gem   |
	 * | txt_coins | img_coins |
	 * \-----------------------/
	 */

	const chirp::vector2f top_right{
		ce::window::size().to<float>().x() - offset,
		offset,
	};

	auto hud_height = static_cast<float>(ts_hud.get_size());
	auto font_offset = (ts_hud.get_size()
		- fnt_hud.text_size(txt_gems).to<int>().y()) / 4;

	pos_gems = {
		top_right.x() - offset - hud_height * scale,
		offset,
	};

	pos_coins = {
		pos_gems.x(),
		pos_gems.y() + hud_height * scale + spacing,
	};

	// Coin
	txt_gems.set_position({
		pos_gems.to<int>().x(),
		pos_gems.to<int>().y() - font_offset,
	});
	// gem
	txt_coins.set_position({
		pos_coins.to<int>().x(),
		pos_coins.to<int>().y() - font_offset,
	});
}

void entity::hud::draw(ce::level &level)
{
	update(level);

	// Text positions
	txt_gems.set_position({
		pos_gems.to<int>().x() - fnt_hud.text_size(txt_gems).to<int>().x(),
		txt_gems.get_position().y(),
	});

	txt_coins.set_position({
		pos_coins.to<int>().x() - fnt_hud.text_size(txt_coins).to<int>().x(),
		txt_coins.get_position().y(),
	});

	// Text
	if (level.get_total_gem_count() > 0)
	{
		fnt_hud.draw_text(txt_gems);
	}
	fnt_hud.draw_text(txt_coins);

	// Coin
	ts_hud.draw(pos_coins.x(), pos_coins.y(),
		static_cast<int>(tile::coin) % static_cast<int>(tile::spawn),
		0.F, scale);
	// Gem
	if (level.get_total_gem_count() > 0)
	{
		ts_hud.draw(pos_gems.x(), pos_gems.y(),
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

auto entity::hud::get_coin_count() const -> int
{
	return state.get_coins();
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

auto entity::hud::get_player_speed_modifier() const -> float
{
	return player_speed_modifier;
}

void entity::hud::set_player_speed_modifier(float value)
{
	player_speed_modifier = value;
}
