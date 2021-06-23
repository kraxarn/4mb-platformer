#pragma once

#include "engine/level.hpp"

class level2: public ce::level
{
public:
	level2();

	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
};
