#pragma once

#include "enum/scenes.hpp"

#include <chirp/assets.hpp>
#include <chirp/scene.hpp>

class state
{
public:
	static auto get() -> std::shared_ptr<chirp::scene>;
	static void set(scene scene, const chirp::assets &assets);

private:
	state() = default;

	static std::shared_ptr<chirp::scene> current;
};
