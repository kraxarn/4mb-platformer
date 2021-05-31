#pragma once

#include "raylib.h"
#include "engine/key.hpp"

#include <iostream>
#include <map>

namespace ce
{
	class input
	{
	public:
		input();

		auto is_pressed(ce::key key) -> bool;

	private:
		std::map<ce::key, int> keyboard;
		std::map<ce::key, int> gamepad;

		int gamepad_index = -1;

		static auto get_gamepad_name() -> std::string;
	};
}
