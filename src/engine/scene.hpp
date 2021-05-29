#pragma once

#include "engine/assets.hpp"

namespace ce
{
	class scene
	{
	public:
		explicit scene(const ce::assets &assets);

		virtual void render() = 0;

	protected:
		const ce::assets &assets;
	};
}
