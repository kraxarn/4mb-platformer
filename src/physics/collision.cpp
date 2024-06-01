#include "physics/collision.hpp"

#include "state.hpp"
#include "physics/tiles.hpp"
#include "scene/scenelevel.hpp"

#include <chirp/collision.hpp>
#include <chirp/os.hpp>

auto phys::collision::get_tile_type(char value) -> tile_type
{
	if (value == static_cast<char>(tile::none))
	{
		return tile_type::empty;
	}

	if (value < static_cast<char>(tile::spawn))
	{
		// 0-3=tile, 4-7=one way
		return value < 4 ? tile_type::tile : tile_type::one_way;
	}

	if (value <= static_cast<char>(tile::spike)) // Last valid tile
	{
		return tile_type::item;
	}

	if (value == static_cast<char>(tile::boss))
	{
		return tile_type::entity;
	}

	return tile_type::invalid;
}

auto phys::collision::update(const chirp::rectangle<float> &player_rect,
	ce::level &level, chirp::vector2f &velocity, entity::hud &hud) -> tile_type
{
	auto collides = tile_type::empty;
	const auto &map = level.map();
	auto rect = player_rect;
	const chirp::vector2f player_position(rect.x(), rect.y());
	auto player_tile = (player_position / ce::tile_size).to<int>();

	// Reset speed modifier
	hud.set_player_speed_modifier(1.F);

	const chirp::rectangle rect_x{
		rect.x() + velocity.x(),
		rect.y(),
		rect.width(),
		rect.height(),
	};

	if (will_collide(level, hud, player_tile, rect_x, velocity))
	{
		velocity = {0, velocity.y()};
		collides = tile_type::tile;
	}

	const chirp::rectangle rect_y{
		rect.x(),
		rect.y() + velocity.y(),
		rect.width(),
		rect.height(),
	};

	if (will_collide(level, hud, player_tile, rect_y, velocity))
	{
		velocity = {velocity.x(), 0};
		collides = tile_type::tile;
	}

	return collides;
}

auto phys::collision::will_collide(ce::level &level, entity::hud &hud,
	const chirp::vector2i &tile, const chirp::rectangle<float> &rect,
	const chirp::vector2f &velocity) -> bool
{
	const auto &map = level.map();
	tile_type tile_type;
	int x;
	int y;

	chirp::rectangle<float> target(0, 0, ce::tile_size, ce::tile_size);

	for (x = tile.x() - offset; x < tile.x() + offset; x++)
	{
		if (x < 0 || x >= map.size())
		{
			continue;
		}

		for (y = tile.y() - offset; y < tile.y() + offset; y++)
		{
			if (y < 0 || y >= map.at(x).size())
			{
				continue;
			}

			tile_type = get_tile_type(map.at(x).at(y));

			target = chirp::rectangle{
				static_cast<float>(x) * ce::tile_size,
				static_cast<float>(y) * ce::tile_size,
				target.width(),
				target.height(),
			};

			if (!chirp::collision::check(rect, target))
			{
				continue;
			}

			if (tile_type == tile_type::tile)
			{
				constexpr float tile_size = ce::tile_size * 0.9F;

				const chirp::rectangle tile_rect{
					rect.x(),
					rect.y() + rect.height() - tile_size,
					rect.width(),
					tile_size,
				};

				if (chirp::collision::check(tile_rect, target))
				{
					return true;
				}
			}

			if (tile_type == tile_type::one_way)
			{
				if (velocity.y() > 0
					&& rect.y() + rect.height() * 0.75F < target.y())
				{
					return true;
				}
			}

			if (tile_type == tile_type::item)
			{
				collect_item(level, hud, x, y);
			}
		}
	}

	return false;
}

auto phys::collision::collect_item(ce::level &level,
	entity::hud &hud, int x, int y) -> bool
{
	const auto &map = level.map();
	const auto &target = map.at(x).at(y);
	auto item = static_cast<::tile>(target);

	if (item == tile::exit)
	{
		if (chirp::os::is_debug()
			|| hud.get_gem_count() == level.get_total_gem_count())
		{
			auto *scene = dynamic_cast<scene_level *>(state::get().get());
			if (scene == nullptr)
			{
				throw std::runtime_error("Reached exit without being in a level");
			}
			scene->next_level();
		}
	}
	else if (item == tile::coin)
	{
		level.set_tile(x, y, -1);
		hud.add_coin();
	}
	else if (item == tile::gem)
	{
		level.set_tile(x, y, -1);
		hud.add_gem();
	}
	else if (item == tile::water)
	{
		hud.set_player_speed_modifier(0.5F);
	}
	else if (item == tile::lava
		|| item == tile::spike)
	{
		hud.kill();
	}

	return true;
}
