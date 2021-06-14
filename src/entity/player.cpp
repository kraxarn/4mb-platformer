#include "player.hpp"

player::player(const ce::assets &assets, phys::physics &physics, float scale)
	: sprite(ce::animated_sprite(assets.tileset("player.png")))
{
	// Sprite
	sprite.set_scale(scale);

	// Physics
	ce::vector2f size = ce::vector2i(sprite.width() - body_offset * 2,
		sprite.height()).to<float>() * scale - body_offset * 2;
	body = physics.add_dynamic_body(size);
}

void player::set_position(const ce::vector2f &position)
{
	body->set_position(position);
	sprite.set_position(position);
}

void player::draw()
{
	sprite.set_position(body->get_position() - static_cast<float>(sprite.width()));
	sprite.draw();
}

auto player::position() const -> ce::vector2f
{
	return sprite.get_position();
}

void player::move(int x)
{
	auto force = 0.F;
	if (x < 0)
	{
		force = -move_force;
	}
	else if (x > 0)
	{
		force = move_force;
	}

	body->set_force(ce::vector2f(force, 0.F));
}

void player::jump()
{
	body->set_force(ce::vector2f(0.F, -jump_force));
}
