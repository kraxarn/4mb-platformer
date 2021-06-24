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

		void begin();
		void end();

	private:
		Shader r_shader = {};
	};
}
