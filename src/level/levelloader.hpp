#pragma once

#include "engine/level.hpp"
#include "level/levels.hpp"

class level_loader
{
public:
	static auto get(int index) -> ce::level *;

private:
	level_loader() = default;
};
