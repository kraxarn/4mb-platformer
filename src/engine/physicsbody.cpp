#include "physicsbody.hpp"

ce::physics_body::physics_body(const ce::vector2f &position,
	const ce::vector2f &size, float density)
{
	auto *body = CreatePhysicsBodyRectangle(Vector2{
		position.x,
		position.y,
	}, size.x, size.y, density);

	id = static_cast<int>(body->id);
}

void ce::physics_body::set_enabled(bool enabled) const
{
	GetPhysicsBody(id)->enabled = enabled;
}
