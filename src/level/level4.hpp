#pragma once

#include "engine/level.hpp"

class level4: public ce::level
{
	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
	auto map() const -> ce::map<char> override;
};
