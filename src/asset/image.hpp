#pragma once

#include "res.hpp"
#include "raylib.h"

namespace asset
{
	class image: public Image
	{
	public:
		explicit image(const cmrc::file &file);

		explicit image(const Image &img);
	};
}
