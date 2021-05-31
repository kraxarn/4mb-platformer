#pragma once

#include "raylib.h"

namespace ce
{
	class clock
	{
	public:
		/** Current FPS */
		static auto fps() -> int;

		/** Seconds since last frame */
		static auto frame_time() -> float;

		/** Seconds since application start */
		static auto time() -> double;
	};
}
