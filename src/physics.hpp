#pragma once

// Constants
constexpr float pixels_per_meter = 100.F;

// Filters
enum class bit: short
{
	nothing = 0,
	destroyed = 1,
	ground = 2,
	platform = 4,
	player = 8,
	coin = 16,
	spike = 32,
	exit = 64,
	boss = 128,
	water = 256,
	player_head = 512,
};
