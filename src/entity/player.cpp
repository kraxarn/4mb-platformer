#include "entity/player.hpp"
#include "scene/scenelevel.hpp"

#include <chirp/colors.hpp>
#include <chirp/log.hpp>
#include <chirp/os.hpp>

entity::player::player(const chirp::assets &assets, const chirp::scene_manager &scenes,
	::entity::hud &hud, float scale)
	: animated_sprite(assets.tileset("player")),
	snd_jump(assets.sound("jump")),
	snd_fall(assets.sound("fall")),
	hud(hud),
	scenes(scenes)
{
	// Sprite
	set_scale(scale);
}

void entity::player::update(const chirp::scene &scene, const float delta)
{
	animated_sprite::update(scene, delta);

	auto *level = dynamic_cast<scene_level *>(&const_cast<chirp::scene &>(scene));
	if (level == nullptr)
	{
		chirp::log::fatal("Player can only exist within a level");
		return;
	}

	const auto &keymap = level->get_keymap();

	if (!level->is_paused())
	{
		auto speed_limit_x = speed_limit * hud.get_player_speed_modifier();

		// Right
		if (keymap.is_down("right"))
		{
			velocity += chirp::vector2f(move_acceleration, 0);
			if (velocity.x() > speed_limit_x)
			{
				velocity = {speed_limit_x, velocity.y()};
			}
		}
		else if (velocity.x() > 0 && is_grounded())
		{
			velocity += chirp::vector2f(move_deceleration, 0);
			if (velocity.x() < 0)
			{
				velocity = {0, velocity.y()};
			}
		}

		// Left
		if (keymap.is_down("left"))
		{
			velocity -= chirp::vector2f(move_acceleration, 0);
			if (velocity.x() < -speed_limit_x)
			{
				velocity = {-speed_limit_x, velocity.y()};
			}
		}
		else if (velocity.x() < 0 && is_grounded())
		{
			velocity -= chirp::vector2f(move_deceleration, 0);
			if (velocity.x() > 0)
			{
				velocity = {0, velocity.y()};
			}
		}

		// Jump
		if (keymap.is_down("jump") && is_grounded())
		{
			snd_jump->play();
			pause();
			set_frame(1);
			velocity = {velocity.x(), jump_force};
		}
		else
		{
			velocity += chirp::vector2f(0, gravity);
		}
	}

	// Update position
	if (!level->is_paused())
	{
		if (!hud.is_dead())
		{
			update_collision(*level->get_level());
		}
		set_position(get_position() + velocity);

		if (velocity.x() == 0)
		{
			pause();
			set_frame(0);
		}
		else if (is_grounded())
		{
			play();
		}
	}

	// Player died or fell out of the stage
	if (get_position().y() > kill_limit)
	{
		if (!hud.is_dead())
		{
			snd_fall->play();
		}
		velocity = chirp::vector2f();
		set_position(level->get_level()->get_safe_spawn());
		hud.respawn();
	}

	// Flip image if needed
	if (get_direction() != get_player_dir())
	{
		flip_horizontal();
	}
}

void entity::player::draw() const
{
	animated_sprite::draw();

	if (chirp::os::is_debug())
	{
		debug_draw(colliding_tile_type == tile_type::tile
			? chirp::colors::green()
			: chirp::colors::red());
	}
}

void entity::player::update_collision(ce::level &level)
{
	colliding_tile_type = phys::collision::update(get_shape(), level, scenes, velocity, hud);
}

auto entity::player::get_velocity() const -> const chirp::vector2f &
{
	return velocity;
}

auto entity::player::is_grounded() const -> bool
{
	return velocity.y() == 0;
}

auto entity::player::get_player_dir() const -> chirp::direction
{
	if (velocity.x() < 0)
	{
		return chirp::direction::left;
	}

	if (velocity.x() > 0)
	{
		return chirp::direction::right;
	}

	return get_direction();
}
