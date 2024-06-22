#pragma once

#include "keymap.hpp"
#include "engine/level.hpp"
#include "engine/map.hpp"

#include "entity/leveltitle.hpp"
#include "entity/map.hpp"
#include "entity/pause.hpp"
#include "entity/player.hpp"

#include <chirp/camera.hpp>
#include <chirp/scene.hpp>

class scene_level: public chirp::scene
{
public:
	explicit scene_level(const chirp::assets &assets);

	void load() override;

	void update(float delta) override;

	void draw() override;

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
	const chirp::assets &assets;

	// Debug
	static constexpr int debug_hud_size = 24;
	static constexpr int debug_hud_offset = 16;

	// Entities
	entity::pause entity_pause;
	entity::level_title entity_level_title;

	// Level switching
	int current_level_index = -1;
	chirp::asset<chirp::sound> snd_complete;

	void update_camera();
	void load_entities();
	void update_entities();

	[[nodiscard]]
	auto get_player() const -> chirp::asset<::entity::player>;

	[[nodiscard]]
	auto get_map() const -> chirp::asset<::entity::map>;

	[[nodiscard]]
	auto get_camera() const -> chirp::asset<chirp::camera>;
};
