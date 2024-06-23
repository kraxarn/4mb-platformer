#pragma once

#include "keymap.hpp"

#include <chirp/animatedsprite.hpp>
#include <chirp/direction.hpp>
#include <chirp/handle.hpp>
#include <chirp/jukebox.hpp>
#include <chirp/scene.hpp>
#include <chirp/sprite.hpp>
#include <chirp/text.hpp>

class scene_menu: public chirp::scene
{
public:
	void load() override;

	void update(float delta) override;

private:
	static constexpr short text_count = 2;
	static constexpr short text_spacing = 48;

	chirp::direction arrow_dir;
	int current = 0;

	std::vector<chirp::asset<chirp::text>> texts;

	// Entity handles
	chirp::handle<chirp::jukebox> jbx_music;
	chirp::handle<chirp::animated_sprite> spr_demo;
	chirp::handle<chirp::text> txt_debug;
	chirp::handle<chirp::sprite> spr_arrow;

	::keymap keymap;

	auto texts_height() -> int;

	void set_current(int value);
	void reset_demo_position();
};
