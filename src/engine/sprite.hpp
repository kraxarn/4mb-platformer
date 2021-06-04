#pragma once

#include "engine/texture.hpp"
#include "engine/movable.hpp"

namespace ce
{
	/**
	 * Static sprite
	 */
	class sprite: public movable
	{
	public:
		explicit sprite(const ce::texture &texture);

		void draw();

	private:
		ce::texture texture;
	};
}
