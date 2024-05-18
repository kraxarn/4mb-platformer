#pragma once

#include <chirp/assets.hpp>

namespace ce
{
	class scene
	{
	public:
		explicit scene(const chirp::assets &assets);

		virtual void render() = 0;

	protected:
		const chirp::assets &assets;
	};
}
