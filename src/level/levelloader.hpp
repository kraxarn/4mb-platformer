#pragma once

#include "engine/level.hpp"

#include <chirp/assets.hpp>

class level_loader
{
public:
	/**
	 * Load level
	 * @note Returns raw pointer
	 */
	static auto get(const chirp::assets &assets, int index) -> ce::level *;

	/**
	 * Is valid level index
	 * @note Does not load level or validate level itself
	 */
	static auto is_valid(int index) -> bool;

private:
	level_loader() = default;
};
