#include "scenelevel.hpp"

scene_level::scene_level(const ce::assets &assets)
	: spr_player(assets.tileset("player.png")),
	music(assets.music("level1.xm")),
	scene(assets)
{
}

void scene_level::render()
{
	music.update();
}

void scene_level::load(int index)
{
	ce::level *new_level = nullptr;

	switch (index)
	{
		case 0:
			new_level = new level1();
			break;
		case 1:
			new_level = new level2();
			break;
		case 2:
			new_level = new level3();
			break;
		case 3:
			new_level = new level4();
			break;
		case 4:
			new_level = new level5();
			break;
		case 5:
			new_level = new level6();
			break;
		case 6:
			new_level = new level7();
			break;
		case 7:
			new_level = new level8();
			break;
		case 8:
			new_level = new level9();
			break;
		case 9:
			new_level = new level10();
			break;
	}

	if (new_level == nullptr)
	{
		std::stringstream stream;
		stream << "Invalid level index: " << index;
		throw std::runtime_error(stream.str());
	}

	level.reset(new_level);

	if (level->music() != music.name())
	{
		std::stringstream stream;
		stream << level->music() << ".xm";
		music = assets.music(stream.str());
	}
	music.play();
}
