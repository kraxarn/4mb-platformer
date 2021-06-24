#include "state.hpp"

std::shared_ptr<ce::scene> state::current = std::shared_ptr<ce::scene>();

auto state::get() -> std::shared_ptr<ce::scene>
{
	return current;
}

void state::set(scene scene, const ce::assets &assets)
{
	ce::scene *new_scene = nullptr;

	switch (scene)
	{
		case scene::menu:
			new_scene = new scene_menu(assets);
			break;

		case scene::level:
			new_scene = new scene_level(assets);
			break;

		case scene::credits:
			new_scene = new scene_credits(assets);
			break;
	}

	if (new_scene != nullptr)
	{
		current.reset(new_scene);
	}
}
