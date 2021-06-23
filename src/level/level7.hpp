#pragma once

#include "engine/level.hpp"

class level7: public ce::level
{
public:
	level7();

	auto name() const -> std::string override;
	auto tileset() const -> std::string override;
	auto music() const -> std::string override;
};
