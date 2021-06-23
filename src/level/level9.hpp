#pragma once

#include "engine/level.hpp"

class level9: public ce::level
{
public:
	level9();

	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
};
