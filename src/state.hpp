#pragma once

#include "scene/scenemenu.hpp"
#include "enum/scenes.hpp"
#include "engine/assets.hpp"

#include <memory>

class state
{
public:
	static auto get() -> std::shared_ptr<ce::scene>;
	static void set(scene scene, const ce::assets &assets);

private:
	state() = default;

	static std::shared_ptr<ce::scene> current;
};
