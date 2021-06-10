#pragma once

#include "engine/assets.hpp"
#include "engine/dynamicbody.hpp"
#include "engine/animatedsprite.hpp"

class player: public ce::animated_sprite
{
public:
	explicit player(const ce::assets &assets);
};
