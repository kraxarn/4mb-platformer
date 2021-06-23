#pragma once

#include "engine/level.hpp"

class level5: public ce::level
{
public:
	level5();

	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
};
