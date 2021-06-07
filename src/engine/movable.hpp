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

		void set_pos(const ce::vector2f &pos);
		void move(float x_offset, float y_offset);

	protected:
		movable() = default;

	private:
		float x;
		float y;
	};
}
