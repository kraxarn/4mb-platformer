#pragma once

#include "raylib.h"

#include <vector>

namespace asset
{
	class image: public Image
	{
	public:
		explicit image(const std::vector<unsigned char> &data);

		explicit image(const Image &img);
	};
}
