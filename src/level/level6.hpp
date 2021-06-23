#pragma once

#include "engine/level.hpp"

class level6: public ce::level
{
public:
	level6();

	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
};
