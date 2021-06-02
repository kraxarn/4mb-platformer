#pragma once

#include "raylib.h"
#include "engine/image.hpp"

#include <string>
#include <iostream>

namespace ce
{
	class window
	{
	public:
		window(int width, int height, const std::string &title, int fps);
		window(int width, int height, const std::string &title);

		~window();

		static auto should_close() -> bool;

		void begin() const;
		void end() const;

		static void close();
		static void set_icon(const ce::image &image);

	private:
		static constexpr int render_width = 1280;
		static constexpr int render_height = 720;

		Camera2D camera = {0};
	};
}
