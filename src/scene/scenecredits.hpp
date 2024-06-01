#pragma once

#include "keymap.hpp"

#include <chirp/assets.hpp>
#include <chirp/scene.hpp>

class scene_credits: public chirp::scene
{
public:
	explicit scene_credits(const chirp::assets &assets);

	void update(float delta) override;

	void draw() override;

	void set_collected_coins(int value);

private:
	static constexpr int size_title = 64;
	static constexpr float spacing = 16;

	chirp::asset<chirp::music> music;

	chirp::asset<chirp::font> fnt_title;
	chirp::text txt_title;

	chirp::asset<chirp::font> fnt_subtitle;
	chirp::text txt_subtitle;

	keymap keymap;
	const chirp::assets &assets;

	auto get_total_coins() -> int;
};
