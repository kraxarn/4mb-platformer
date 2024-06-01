#include "state.hpp"

#include "scene/scenecredits.hpp"
#include "scene/scenelevel.hpp"
#include "scene/scenemenu.hpp"

std::shared_ptr<chirp::scene> state::current = std::shared_ptr<chirp::scene>();

auto state::get() -> std::shared_ptr<chirp::scene>
{
	return current;
}

void state::set(scene scene, const chirp::assets &assets)
{
	chirp::scene *new_scene = nullptr;

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
