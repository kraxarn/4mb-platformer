#pragma once

#include "raylib.h"
#include "asset/image.hpp"

#include <cmath>

namespace ce
{
	class texture
	{
	public:
		explicit texture(const asset::image &image);

		/**
		 * Draw entire texture at position
		 * @param x X position
		 * @param y Y position
		 */
		void draw(float x, float y);

		/**
		 * Draw part of texture
		 * @param x X position
		 * @param y Y position
		 * @param size Texture width/height
		 * @param offset X offset in position
		 */
		void draw(float x, float y, int size, int offset) const;

		/**
		 * Draw part of texture with rotation and scale
		 * @param x X position
		 * @param y Y position
		 * @param size Texture width/height
		 * @param offset X offset in position
		 * @param rotation
		 */
		void draw(float x, float y, int size, int offset,
			float rotation, float scale) const;

		auto get_width() const -> int;
		auto get_height() const -> int;

	private:
		Texture2D r_texture;
	};
}
