#pragma once

#include <chirp/map.hpp>

namespace ce
{
	/** How much to scale each tile before displaying */
	static constexpr auto tile_scale = 3.F;

	/** Total tile size with scaling applied */
	static constexpr float tile_size = chirp::tileset_size * tile_scale;
}
