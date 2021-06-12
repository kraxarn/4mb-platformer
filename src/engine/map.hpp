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
	template<typename TPos, typename TMap>
	void iterate_map(const map<TMap> &map,
		const std::function<bool(TPos, TPos, TMap)> &iter)
	{
		for (TPos x = 0; x < map.size(); x++)
		{
			for (TPos y = 0; y < map.at(y).size(); y++)
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
	template<typename TPos, typename TMap>
	void iterate_map_all(const map<TMap> &map,
		const std::function<void(TPos, TPos, TMap)> &iter)
	{
		for (TPos x = 0; x < map.size(); x++)
		{
			for (TPos y = 0; y < map.at(y).size(); y++)
			{
				iter(x, y, map.at(x).at(y));
			}
		}
	}
}
