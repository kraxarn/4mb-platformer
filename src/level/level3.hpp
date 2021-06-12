#pragma once

#include "engine/level.hpp"

class level3: public ce::level
{
public:
	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
	auto map() const -> ce::map<char> override;
};
