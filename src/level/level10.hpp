#pragma once

#include "engine/level.hpp"

class level10: public ce::level
{
public:
	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
	auto map() const -> std::array<std::array<char, 25>, 75> override;
};
