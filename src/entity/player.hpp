#pragma once

#include "engine/assets.hpp"
#include "engine/animatedsprite.hpp"
#include "engine/map.hpp"
#include "engine/rect.hpp"
#include "engine/movable.hpp"
#include "engine/input.hpp"

class player: public ce::animated_sprite
{
public:
	player(const ce::assets &assets, float scale);

	void update(const ce::input &input, const ce::level &level);

	auto get_velocity() const -> const ce::vector2f &;

	auto rect() const -> Rectangle;

#ifndef NDEBUG
	void debug_draw() const;
#endif

private:
	static constexpr float move_force = 1.F;
	static constexpr float jump_force = 1.F;

	ce::vector2f velocity;
};
