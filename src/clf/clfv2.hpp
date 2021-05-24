#pragma once

#include "clf/clfloader.hpp"

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

/**
 * CLF Version 2 (binary format)
 */
class clf_v2
{
public:
	static auto parse(const std::filesystem::path &path) -> clf;

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
};