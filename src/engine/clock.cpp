#include "clock.hpp"

auto ce::clock::fps() -> int
{
	return GetFPS();
}

auto ce::clock::frame_time() -> float
{
	return GetFrameTime();
}

auto ce::clock::time() -> double
{
	return GetTime();
}
