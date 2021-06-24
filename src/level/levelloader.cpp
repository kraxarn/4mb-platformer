#include "levelloader.hpp"

auto level_loader::get(int index) -> ce::level *
{
	switch (index)
	{
		case 0:
			return new level1();
		case 1:
			return new level2();
		case 2:
			return new level3();
		case 3:
			return new level4();
		case 4:
			return new level5();
		case 5:
			return new level6();
		case 6:
			return new level7();
		case 7:
			return new level8();
		case 8:
			return new level9();
		case 9:
			return new level10();
		default:
			return nullptr;
	}
}

auto level_loader::is_valid(int index) -> bool
{
	return index >= 0 && index <= 9;
}
