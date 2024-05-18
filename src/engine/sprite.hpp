#pragma once

#include "engine/movable.hpp"

#include <chirp/texture.hpp>

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
		explicit sprite(const chirp::texture &texture);

		/**
		 * New sprite from image
		 */
		explicit sprite(const chirp::image &image);

		void draw();

		auto width() const -> int;
		auto height() const -> int;

	private:
		chirp::texture texture;
	};
}
