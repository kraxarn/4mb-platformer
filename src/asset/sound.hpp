#pragma once

#include "raylib.h"

#include <vector>

namespace asset
{
	class sound
	{
	public:
		explicit sound(const std::vector<unsigned char> &data);
		~sound();

		void play();

	private:
		Sound r_sound = {};
		Wave r_wave = {};
	};
}
