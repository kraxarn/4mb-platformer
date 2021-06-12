#pragma once

#include <array>
#include <functional>

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

	/**
	 * Iterate through parts of map, returning true to stop iterating
	 */
	template<typename T>
	void iterate_map(const map<T> &map,
		const std::function<bool(std::size_t, std::size_t, T)> &iter)
	{
		for (std::size_t x = 0; x < map.size(); x++)
		{
			for (std::size_t y = 0; y < map.at(y).size(); y++)
			{
				if (iter(x, y, map.at(x).at(y)))
				{
					return;
				}
			}
		}
	}

	/**
	 * Iterate through entire map
	 */
	template<typename T>
	void iterate_map_all(const map<T> &map,
		const std::function<void(std::size_t, std::size_t, T)> &iter)
	{
		for (std::size_t x = 0; x < map.size(); x++)
		{
			for (std::size_t y = 0; y < map.at(y).size(); y++)
			{
				iter(x, y, map.at(x).at(y));
			}
		}
	}
}
