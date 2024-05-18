#pragma once

#include "engine/input.hpp"
#include "engine/scene.hpp"

#include "state.hpp"

#include <chirp/assets.hpp>

class scene_credits: public ce::scene
{
public:
	explicit scene_credits(const chirp::assets &assets);

	void render() override;

	void set_collected_coins(int value);

private:
	static constexpr int size_title = 64;
	static constexpr float spacing = 16;

	chirp::asset<chirp::music> music;

	chirp::asset<chirp::font> fnt_title;
	chirp::text txt_title;

	chirp::asset<chirp::font> fnt_subtitle;
	chirp::text txt_subtitle;

	ce::input input;

	auto get_total_coins() -> int;
};
