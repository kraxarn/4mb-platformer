#include "transition.hpp"

void entity::transition::expand(const ce::vector2f &end, std::function<void()> callback)
{
	expand_callback = std::move(callback);
	dir = entity::transition::direction::expanding;
	speed = 0;
	position = end.to<int>();
	size = 0.F;
}

void entity::transition::shrink(const ce::vector2f &end, std::function<void()> callback)
{
	shrink_callback = std::move(callback);
	dir = entity::transition::direction::shrinking;
	speed = 0;
	position = end.to<int>();
	size = ce::window::size().to<float>().x / 2.F;
}

void entity::transition::update()
{
	if (dir == entity::transition::direction::none)
	{
		return;
	}

	speed++;
	size += dir == entity::transition::direction::expanding
		? speed : -speed;

	DrawCircle(position.x, position.y,
		size, BLACK);
}
