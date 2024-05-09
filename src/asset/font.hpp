#pragma once

#include "raylib.h"
#include "engine/text.hpp"

#include <vector>

namespace asset
{
	class font
	{
	public:
		font(const std::vector<unsigned char> &data, int font_size);
		~font();

		void draw_text(const ce::text &text) const;
		auto text_size(const ce::text &text) const -> Vector2;

		auto font_size() const -> int;

	private:
		Font r_font = {};
		int *font_chars = nullptr;
	};
}
