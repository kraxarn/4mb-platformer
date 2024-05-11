#pragma once

#include <chirp/vector2.hpp>

namespace ce
{
	/**
	 * Entity with a position
	 */
	class movable
	{
	public:
		auto get_x() const -> float;
		void set_x(float value);

		auto get_y() const -> float;
		void set_y(float value);

		void set_position(const chirp::vector2f &new_pos);
		auto get_position() const -> chirp::vector2f;

		void move(float x_offset, float y_offset);

	protected:
		movable() = default;

	private:
		chirp::vector2f pos;
	};
}
