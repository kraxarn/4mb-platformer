#pragma once

#include "raylib.h"

#include <chirp/image.hpp>
#include <chirp/vector2.hpp>

#include <iostream>
#include <string>

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
		static void set_icon(const chirp::image &image);

		static auto size() -> chirp::vector2i;

	private:
		Camera2D camera = {0};
	};
}
