#pragma once

#include "engine/level.hpp"

class level10: public ce::level
{
public:
	level10();

	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
};
