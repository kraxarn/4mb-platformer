#pragma once

#include "engine/level.hpp"

class level4: public ce::level
{
public:
	level4();

	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
};
