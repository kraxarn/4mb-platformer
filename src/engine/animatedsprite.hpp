#pragma once

#include "asset/tileset.hpp"
#include "engine/movable.hpp"
#include "enum/direction.hpp"

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

		void flip();
		auto get_dir() const -> direction;

		auto width() const -> int;
		auto height() const -> int;
		auto size() const -> ce::vector2i;

		void set_frame(int index);

		void pause();
		void resume();

		/** Raylib style collision rectangle */
		auto rect() const -> Rectangle;

#ifndef NDEBUG
	protected:
		void debug_draw(const Color &color) const;
#endif

	private:
		/** Ticks between switching frame */
		int time = 10;

		/** Current tick */
		int current = 0;

		/** Current frame */
		int frame = 0;

		float scale = 1.F;

		float rotation = 0.F;

		/** Animation is running */
		bool running = true;

		asset::tileset tileset;

		direction dir = direction::left;
	};
}
