#pragma once

#include <array>

namespace ce
{
	/** Maximum number of tiles horizontally */
	static constexpr int level_tiles_width = 75;

	/** Maximum number of tiles vertically */
	static constexpr int level_tiles_height = 25;

	/**
	 * Level map data
	 */
	template<typename T>
	using map = std::array<std::array<T, level_tiles_height>, level_tiles_width>;
}
