#pragma once

#include "engine/tileset.hpp"

namespace ce
{
	/**
	 * Animated sprite
	 */
	class sprite
	{
	public:
		explicit sprite(const ce::tileset &tileset);

		void draw();

		void set_pos(float x, float y);
		void move(float x, float y);

		auto x() const -> float;
		auto y() const -> float;

		void set_scale(float scale);

		void rotate(float value);

	private:
		/** Ticks between switching frame */
		int time = 10;

		/** Current tick */
		int current = 0;

		/** Current frame */
		int frame = 0;

		float scale = 1.F;

		float rotation = 0.F;

		ce::tileset tileset;
	};
}
