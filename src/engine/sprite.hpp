#pragma once

#include "engine/movable.hpp"

#include <chirp/asset.hpp>
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
		explicit sprite(const chirp::asset<chirp::texture> &texture);

		/**
		 * New sprite from image
		 */
		explicit sprite(const chirp::asset<chirp::image> &image);

		void draw();

		auto width() const -> int;
		auto height() const -> int;

	private:
		chirp::asset<chirp::texture> texture;
	};
}
