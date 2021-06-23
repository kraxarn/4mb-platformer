#pragma once

#include "engine/level.hpp"

class level1: public ce::level
{
public:
	level1();

	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
};
