#pragma once

#include "engine/level.hpp"

#include <vector>

namespace asset
{
	class level: public ce::level
	{
	public:
		explicit level(const std::vector<unsigned char> &data);

		auto name() const -> std::string override;
		auto tileset() const -> std::string override;
		auto music() const -> std::string override;
		auto map() const -> const ce::map<char> & override;
		void set_tile(int x, int y, char value) override;
		auto type() const -> std::string override;

	private:
		std::string name_data;
		std::string tileset_data;
		std::string music_data;
		std::string level_type;
		ce::map<char> map_data;

		void parse(const std::vector<unsigned char> &level_data);
		static auto parse_tile(const std::string &line, size_t start, size_t end) -> char;
	};
}
