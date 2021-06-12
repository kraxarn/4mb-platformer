#include "player.hpp"

player::player(const ce::assets &assets, ce::physics &physics, float scale)
	: sprite(ce::animated_sprite(assets.tileset("player.png")))
{
	// Sprite
	sprite.set_scale(scale);

	// Physics
	ce::vector2f spawn;
	ce::vector2f size = ce::vector2i(sprite.width(), sprite.height()).to<float>() * scale;
	body = physics.add_dynamic_body(spawn, size);
}

void player::set_position(const ce::vector2f &position)
{
	body->set_position(position);
	sprite.set_pos(position);
}

void player::draw()
{
	sprite.set_pos(body->get_position() - static_cast<float>(sprite.width()));
	sprite.draw();
}

auto player::position() const -> ce::vector2f
{
	return sprite.get_pos();
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

	body->add_force(ce::vector2f(force, 0.F));
}

void player::jump()
{
	body->add_force(ce::vector2f(0.F, -jump_force));
}
