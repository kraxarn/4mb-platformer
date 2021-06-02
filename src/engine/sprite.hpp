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

	private:
		/** Ticks between switching frame */
		int time = 200;

		/** Current tick */
		int current = 0;

		/** Current frame */
		int frame = 0;

		ce::tileset tileset;
	};
}
