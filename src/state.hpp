#pragma once

#include "enum/scenes.hpp"
#include "scene/scenelevel.hpp"
#include "scene/scenemenu.hpp"

#include <chirp/assets.hpp>

class state
{
public:
	static auto get() -> std::shared_ptr<ce::scene>;
	static void set(scene scene, const chirp::assets &assets);

private:
	state() = default;

	static std::shared_ptr<ce::scene> current;
};
