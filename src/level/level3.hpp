#pragma once

#include "engine/level.hpp"

class level3: public ce::level
{
public:
	level3();

	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
};
