#pragma once

#include "asset/tileset.hpp"
#include "engine/movable.hpp"

namespace ce
{
	/**
	 * Animated sprite
	 */
	class animated_sprite: public ce::movable
	{
	public:
		explicit animated_sprite(const asset::tileset &tileset);

		void draw();

		auto get_scale() const -> float;
		void set_scale(float scale);

		void rotate(float value);

		auto width() const -> int;
		auto height() const -> int;
		auto size() const -> ce::vector2i;

	private:
		/** Ticks between switching frame */
		int time = 10;

		/** Current tick */
		int current = 0;

		/** Current frame */
		int frame = 0;

		float scale = 1.F;

		float rotation = 0.F;

		asset::tileset tileset;
	};
}
