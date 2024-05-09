#include "level.hpp"

#include <sstream>

asset::level::level(const std::vector<unsigned char> &data)
	: ce::level(),
	map_data({})
{
	parse(data);
}

auto asset::level::name() const -> std::string
{
	return name_data;
}

auto asset::level::tileset() const -> std::string
{
	return tileset_data;
}

auto asset::level::music() const -> std::string
{
	return music_data;
}

auto asset::level::map() const -> const ce::map<char> &
{
	return map_data;
}

auto asset::level::type() const -> std::string
{
	return level_type;
}

void asset::level::set_tile(const int x, const int y, const char value)
{
	map_data.at(x).at(y) = value;
}

void asset::level::parse(const std::vector<unsigned char> &level_data)
{
	std::string data(level_data.cbegin(), level_data.cend());
	std::istringstream stream(data);
	std::string line;

	while (std::getline(stream, line))
	{
		const auto split = line.find('=');
		if (split != std::string::npos)
		{
			const auto key = line.substr(0, split);
			const auto value = line.substr(split + 1);

			if (key == "name")
			{
				name_data = value;
			}
			else if (key == "tileset")
			{
				tileset_data = value;
			}
			else if (key == "music")
			{
				music_data = value;
			}
			else if (key == "type")
			{
				level_type = value;
			}
			continue;
		}

		if (line == "[map]")
		{
			size_t y_index = 0;

			while (std::getline(stream, line))
			{
				size_t x_index = 0;
				size_t start = 0;
				size_t end = line.find(' ');

				while (end != std::string::npos)
				{
					map_data.at(y_index).at(x_index) = parse_tile(line, start, end);
					start = end + 1;
					end = line.find(' ', start);
					x_index++;
				}

				map_data.at(y_index).at(x_index) = parse_tile(line, start, end);
				y_index++;
			}
		}
	}
}

auto asset::level::parse_tile(const std::string &line, const size_t start, const size_t end) -> char
{
	const auto str_val = line.substr(start, end - start);
	const auto int_val = std::stoi(str_val);
	return static_cast<char>(int_val);
}
