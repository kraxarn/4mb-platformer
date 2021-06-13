#pragma once

#include "engine/vector2.hpp"

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

		void set_position(const ce::vector2f &new_pos);
		auto get_position() const -> ce::vector2f;

		void move(float x_offset, float y_offset);

	protected:
		movable() = default;

	private:
		ce::vector2f pos;
	};
}
