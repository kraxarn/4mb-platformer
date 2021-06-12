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

ce::physics_body::~physics_body()
{
	DestroyPhysicsBody(GetPhysicsBody(id));
}

void ce::physics_body::set_enabled(bool enabled) const
{
	GetPhysicsBody(id)->enabled = enabled;
}

auto ce::physics_body::get_position() const -> ce::vector2f
{
	const auto *body = GetPhysicsBody(id);
	return {
		body->position.x,
		body->position.y,
	};
}

#ifndef NDEBUG
void ce::physics_body::draw(Color color) const
{
	auto *body = GetPhysicsBody(id);
	auto vertices = GetPhysicsShapeVerticesCount(id);

	for (int j = 0; j < vertices; j++)
	{
		DrawLineV(GetPhysicsShapeVertex(body, j),
			GetPhysicsShapeVertex(body, j + 1 < vertices ? j + 1 : 0),
			color);
	}
}
#endif
