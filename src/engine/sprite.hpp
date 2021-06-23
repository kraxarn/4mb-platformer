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
		/**
		 * New sprite from texture
		 */
		explicit sprite(const ce::texture &texture);

		/**
		 * New sprite from image
		 */
		explicit sprite(const asset::image &image);

		void draw();

		auto width() const -> int;
		auto height() const -> int;

	private:
		ce::texture texture;
	};
}
