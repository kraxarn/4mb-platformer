#pragma once

#include "raylib.h"
#include "engine/image.hpp"

namespace ce
{
	class texture: public Texture2D
	{
	public:
		explicit texture(const ce::image &image);
	};
}
