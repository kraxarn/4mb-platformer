#include "camera.hpp"

ce::camera::camera()
{
	r_camera.zoom = 1.F;
}

void ce::camera::begin() const
{
	BeginMode2D(r_camera);
}

void ce::camera::end() const
{
	EndMode2D();
}

void ce::camera::set_target(const ce::vector2f &target)
{
	r_camera.target.x = target.x;
	r_camera.target.y = target.y;
}

auto ce::camera::get_offset() const -> ce::vector2f
{
	return {r_camera.offset.x, r_camera.offset.y};
}

void ce::camera::set_offset(const ce::vector2f &offset)
{
	r_camera.offset.x = offset.x;
	r_camera.offset.y = offset.y;
}

void ce::camera::move(float x, float y)
{
	r_camera.target.x += x;
	r_camera.target.y += y;
}

auto ce::camera::get_x() const -> float
{
	return r_camera.target.x;
}

void ce::camera::set_x(float x)
{
	r_camera.target.x = x;
}

auto ce::camera::get_y() const -> float
{
	return r_camera.target.y;
}

void ce::camera::set_y(float y)
{
	r_camera.target.y = y;
}
