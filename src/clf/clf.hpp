#pragma once

#include "enum/leveltype.hpp"
#include "vec2.hpp"

#include <string>
#include <vector>

/**
 * CLF level data
 */
class clf
{
public:
	clf() = default;

	/** CLF version number */
	int version = 3;

	/** Level title */
	std::string name;

	/** Filename of music file */
	std::string music;

	/** Filename of main tileset (1-49) */
	std::string main_tileset;

	/** Filename of item tileset (50+) */
	std::string item_tileset;

	/** Size in px of tiles */
	int tile_size = 64;

	/** Filename of background image */
	std::string background;

	/** Type of level */
	e::level_type level_type = e::level_type::normal;

	/** Size of level map */
	vec2 map_size = vec2(75, 25);

	/** Map data */
	std::vector<std::vector<unsigned char>> map;

	/** String interpretation of level type */
	[[nodiscard]] auto level_type_string() const -> std::string;
};
