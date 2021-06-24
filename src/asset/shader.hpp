#pragma once

#include "raylib.h"
#include "res.hpp"

namespace asset
{
	class shader
	{
	public:
		explicit shader(const cmrc::file &file);
		~shader();

	private:
		Shader r_shader = {};
	};
}
