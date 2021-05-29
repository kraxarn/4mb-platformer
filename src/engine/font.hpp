#pragma once

#include "raylib.h"
#include "res.hpp"
#include "engine/text.hpp"

namespace ce
{
	class font
	{
	public:
		font(const cmrc::file &file, int font_size);
		~font();

		void draw_text(const ce::text &text) const;

	private:
		Font r_font = {};
		int *font_chars = nullptr;
	};
}