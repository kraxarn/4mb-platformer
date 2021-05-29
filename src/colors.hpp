#pragma once

#include "raylib.h"

class color
{
public:
	static Color background;

	static Color text;

private:
	color() = default;
};

Color color::background = {0x33, 0x99, 0xda, 0xff};

Color color::text = {0xf5, 0xf5, 0xf5, 0xff};
