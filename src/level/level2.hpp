#pragma once

#include "engine/level.hpp"

class level2: public ce::level
{
	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
	auto map() const -> std::array<std::array<char, 25>, 75> override;
};


