#pragma once

#include "raylib.h"
#include "asset/image.hpp"
#include "engine/vector2.hpp"

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
		static void set_icon(const asset::image &image);

		static auto size() -> ce::vector2i;

	private:
		Camera2D camera = {0};
	};
}
