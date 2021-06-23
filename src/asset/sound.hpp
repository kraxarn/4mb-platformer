#pragma once

#include "raylib.h"
#include "res.hpp"

namespace asset
{
	class sound
	{
	public:
		explicit sound(const cmrc::file &file);
		~sound();

		void play();

	private:
		Sound r_sound = {};
		Wave r_wave = {};
	};
}
