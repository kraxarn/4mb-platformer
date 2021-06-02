#pragma once

#include "res.hpp"
#include "engine/texture.hpp"

#include <vector>

namespace ce
{
	class tileset
	{
	public:
		explicit tileset(const cmrc::file &file);

		void set_index(int index);

		auto at(int index) const -> ce::image;

		void draw(int index) const;
		void draw(int index, float rotation, float scale) const;

		auto get_size() const -> int;

		void set_pos(float x, float y);
		auto x() const -> float;
		auto y() const -> float;

		void move(float x, float y);

	private:
		/** Total size for each tile */
		int size = 0;

		/** Current index */
		int index = 0;

		/** Number of tiles */
		int count = 0;

		ce::image image;
		ce::texture texture;
	};
}
