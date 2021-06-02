#pragma once

#include "res.hpp"
#include "raylib.h"

namespace ce
{
	class image: public Image
	{
	public:
		explicit image(const cmrc::file &file);

		explicit image(const Image &img);
	};
}
