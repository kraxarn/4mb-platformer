#pragma once

#include <chirp/texture.hpp>

#include <vector>

namespace asset
{
	class tileset
	{
	public:
		explicit tileset(const std::vector<unsigned char> &data);

		auto at(int index) const -> chirp::image;

		void draw(float x, float y, int index, float rotation, float scale) const;

		void flip_horizontal();

		auto get_size() const -> int;

	private:
		/** Total size for each tile */
		int size = 0;

		chirp::image image;
		chirp::texture texture;
	};
}
