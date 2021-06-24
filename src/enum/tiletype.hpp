#pragma once

enum class tile_type
{
	// -1
	empty,
	// 0-49
	tile,
	one_way,
	// 50-99
	item,
	entity,
	// ???
	invalid,
};
