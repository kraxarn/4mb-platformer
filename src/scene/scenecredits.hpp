#pragma once

#include "keymap.hpp"

#include <chirp/asset.hpp>
#include <chirp/font.hpp>
#include <chirp/handle.hpp>
#include <chirp/scene.hpp>
#include <chirp/text.hpp>

class scene_credits: public chirp::scene
{
public:
	explicit scene_credits(int collected_coint_count);

	void load() override;

	void update(float delta) override;

	void set_collected_coins(int value);

private:
	static constexpr int size_title = 64;
	static constexpr float spacing = 16;

	chirp::asset<chirp::font> fnt_title;
	chirp::asset<chirp::font> fnt_subtitle;

	chirp::handle<chirp::text> txt_title;
	chirp::handle<chirp::text> txt_subtitle;

	::keymap keymap;

	int collected_count_count;

	auto get_total_coins() -> int;
};
