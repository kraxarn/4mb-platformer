#pragma once

#include "res.hpp"
#include "engine/texture.hpp"

#include <vector>

namespace asset
{
	class tileset
	{
	public:
		explicit tileset(const cmrc::file &file);

		void set_index(int index);

		auto at(int index) const -> asset::image;

		void draw(float x, float y, int index) const;
		void draw(float x, float y, int index, float rotation, float scale) const;

		auto get_size() const -> int;

	private:
		/** Total size for each tile */
		int size = 0;

		/** Current index */
		int index = 0;

		/** Number of tiles */
		int count = 0;

		asset::image image;
		ce::texture texture;
	};
}
