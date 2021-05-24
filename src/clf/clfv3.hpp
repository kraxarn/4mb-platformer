#pragma once

#include "clf/clf.hpp"

#include <sstream>
#include <filesystem>
#include <fstream>

/**
 * CLF version 3, ini-like format
 */
class clf_v3
{
public:
	static auto save(const clf &level, const std::filesystem::path &path) -> bool;
};
