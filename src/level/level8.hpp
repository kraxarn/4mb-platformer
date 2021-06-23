#pragma once

#include "engine/level.hpp"

class level8: public ce::level
{
public:
	level8();

	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
};
