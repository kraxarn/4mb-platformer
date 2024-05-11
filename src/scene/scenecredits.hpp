#pragma once

#include "engine/scene.hpp"
#include "engine/assets.hpp"
#include "engine/vector2.hpp"
#include "engine/window.hpp"
#include "engine/map.hpp"
#include "engine/input.hpp"

#include "colors.hpp"
#include "level/levelloader.hpp"
#include "state.hpp"

class scene_credits: public ce::scene
{
public:
	explicit scene_credits(const ce::assets &assets);

	void render() override;

	void set_collected_coins(int value);

private:
	static constexpr int size_title = 64;
	static constexpr float spacing = 16;

	chirp::music music;

	asset::font fnt_title;
	ce::text txt_title;
	chirp::text txt_title;

	asset::font fnt_subtitle;
	ce::text txt_subtitle;

	ce::input input;

	auto get_total_coins() -> int;
};
