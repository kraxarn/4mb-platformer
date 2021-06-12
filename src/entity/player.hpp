#pragma once

#include "engine/assets.hpp"
#include "engine/dynamicbody.hpp"
#include "engine/animatedsprite.hpp"
#include "engine/physics.hpp"
#include "engine/physicsconfig.hpp"

class player
{
public:
	explicit player(const ce::assets &assets, ce::physics &physics, float scale);

	void set_position(const ce::vector2f &position);

	void draw();
	auto position() const -> ce::vector2f;

	/**
	 * Move in direction
	 * @param x <0 for left, 0> for right
	 */
	void move(int x);
	void jump();

private:
	static constexpr float move_force = 0.2F;
	static constexpr float jump_force = 3.F;

	ce::animated_sprite sprite;
	std::shared_ptr<ce::dynamic_body> body;
};
