#include "player.hpp"

player::player(const ce::assets &assets)
	: ce::animated_sprite(assets.tileset("player.png"))
{

}
