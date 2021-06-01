#include "state.hpp"

std::shared_ptr<ce::scene> state::current = std::shared_ptr<ce::scene>();

auto state::get() -> std::shared_ptr<ce::scene>
{
	return current;
}

void state::set(scene scene, const ce::assets &assets)
{
	switch (scene)
	{
		case scene::menu:
			current = std::make_shared<scene_menu>(assets);
			break;
	}
}
