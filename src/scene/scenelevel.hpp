#pragma once

#include "keymap.hpp"
#include "engine/level.hpp"
#include "engine/map.hpp"

#include "entity/leveltitle.hpp"
#include "entity/map.hpp"
#include "entity/pause.hpp"
#include "entity/player.hpp"

#include <chirp/camera.hpp>
#include <chirp/handle.hpp>
#include <chirp/jukebox.hpp>
#include <chirp/scene.hpp>

#include "entity/boss.hpp"

class scene_level: public chirp::scene
{
public:
	void load() override;

	void update(float delta) override;

	/** Load specific level */
	void load(int index);

	/** Go to next level */
	void next_level();

	[[nodiscard]]
	auto is_paused() const -> bool;

	[[nodiscard]]
	auto get_keymap() const -> const ::keymap &;

	[[nodiscard]]
	auto get_level() const -> ce::level *;

private:
	static constexpr int level_width = chirp::level_tiles_width * ce::tile_size;
	static constexpr int level_height = chirp::level_tiles_height * ce::tile_size;

	// General engine stuff
	::keymap keymap;

	// Debug
	static constexpr int debug_hud_size = 24;
	static constexpr int debug_hud_offset = 16;

	// Entity handles
	chirp::handle<chirp::camera> camera_main;
	chirp::handle<chirp::jukebox> jbx_music;
	chirp::handle<chirp::text> text_debug;
	chirp::handle<entity::boss> entity_boss;
	chirp::handle<entity::hud> entity_hud;
	chirp::handle<entity::level_title> entity_level_title;
	chirp::handle<entity::map> entity_map;
	chirp::handle<entity::pause> entity_pause;
	chirp::handle<entity::player> entity_player;

	// Level switching
	int current_level_index = -1;
	chirp::asset<chirp::sound> snd_complete;

	void update_camera();
	void update_camera_zoom() const;
	void load_entities();
	void update_entities();
};
