#pragma once

#include "vec2.hpp"

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

/**
 * Level file
 */
class clf
{
public:
	/** Load level file from path */
	auto load(const std::filesystem::path &path) -> bool;

	auto background() const -> std::string;

	auto is_boss() const -> bool;

	auto map_size() const -> vec2;

	auto tile_size() const -> int;

	auto main_tileset() const -> std::string;

	auto item_tileset() const -> std::string;

	auto map() const -> std::array<std::array<unsigned char, 25>, 75>;

private:
	struct clf_v2_data
	{
		int version = 2;
		char background[16] = {0};
		bool is_boss = false;
		int map_size[2] = {0};
		int tile_size = 0;
		char main_tileset[16] = {0};
		char item_tileset[16] = {0};
		int map[75][25] = {0};
	};

	struct clf_v2_data data;
};

