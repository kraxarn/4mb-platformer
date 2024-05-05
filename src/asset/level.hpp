#pragma once
#include <cmrc/cmrc.hpp>

#include "engine/level.hpp"

namespace asset
{
	class level: public ce::level
	{
	public:
		explicit level(const cmrc::file &file);

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

		void parse(const cmrc::file &file);
		static auto parse_tile(const std::string &line, size_t start, size_t end) -> char;
	};
}
