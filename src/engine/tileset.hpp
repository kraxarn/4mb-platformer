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

	private:
		/** Total size for each tile */
		int size = 0;

		/** Number of tiles */
		int count = 0;

		ce::texture texture;
	};
}
