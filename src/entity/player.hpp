#pragma once

#include "engine/assets.hpp"
#include "engine/animatedsprite.hpp"
#include "engine/map.hpp"
#include "physics/dynamicbody.hpp"
#include "physics/physics.hpp"
#include "physics/config.hpp"

class player
{
public:
	explicit player(const ce::assets &assets, phys::physics &physics, float scale);

	void set_position(const ce::vector2f &position);

	void draw();
	auto position() const -> ce::vector2f;
	auto force() const -> ce::vector2f;

	/**
	 * Move in direction
	 * @param x <0 for left, 0> for right
	 */
	void move(int x);
	void jump();

private:
	static constexpr float move_force = 50000.F;
	static constexpr float jump_force = 300.F;

	static constexpr int body_offset = static_cast<int>(ce::tile_size * 0.25F);

	ce::animated_sprite sprite;
	std::shared_ptr<phys::dynamic_body> body;
};
