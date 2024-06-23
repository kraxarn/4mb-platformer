#include "engine/map.hpp"
#include "entity/map.hpp"
#include "enum/tiletype.hpp"
#include "physics/collision.hpp"
#include "physics/tiles.hpp"

#include <chirp/colors.hpp>
#include <chirp/entitycontainer.hpp>
#include <chirp/log.hpp>
#include <chirp/os.hpp>
#include <chirp/scene.hpp>

entity::map::~map()
{
	delete level;
}

void entity::map::update(const chirp::scene &scene, const float /*delta*/)
{
	if (level == nullptr)
	{
		return;
	}

	const auto &ent_hud = scene.entities().find<::entity::hud>("ent_hud");
	gem_count = ent_hud->get_gem_count();
}

void entity::map::draw() const
{
	if (level == nullptr)
	{
		chirp::log::warn("not drawing map, no map loaded");
		return;
	}

	for (const auto &tile: level->tiles())
	{
		const auto tile_type = phys::collision::get_tile_type(tile.value);
		if (tile_type == tile_type::empty)
		{
			continue;
		}

		const auto x_pos = static_cast<float>(tile.x) * ce::tile_size;
		const auto y_pos = static_cast<float>(tile.y) * ce::tile_size;

		if (tile_type == tile_type::tile || tile_type == tile_type::one_way)
		{
			tiles->draw({x_pos, y_pos},
				tile.value, 0.F, ce::tile_scale);
		}
		else if (tile_type == tile_type::item)
		{
			if (tile.value != static_cast<char>(tile::exit)
				|| gem_count == level->get_total_gem_count())
			{
				items->draw({x_pos, y_pos},
					tile.value % static_cast<int>(tile::spawn),
					0.F, ce::tile_scale);
			}
		}

		if (chirp::os::is_debug())
		{
			const chirp::rectangle<float> outline{
				tile.x * ce::tile_size,
				tile.y * ce::tile_size,
				ce::tile_size,
				ce::tile_size,
			};

			chirp::draw_outline(outline.to<int>(), chirp::colors::green());
		}
	}
}

auto entity::map::get_level() const -> ce::level *
{
	return level;
}

void entity::map::set_level(const chirp::assets &assets, ce::level *level)
{
	tiles = assets.tileset(level->tileset());

	if (!items)
	{
		items = assets.tileset("items");
	}

	delete this->level;
	this->level = level;
}
