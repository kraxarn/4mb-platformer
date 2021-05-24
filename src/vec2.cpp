#include "vec2.hpp"

vec2::vec2(int x, int y)
	: x(x), y(y)
{
}

auto vec2::to_string() const -> std::string
{
	std::stringstream stream;
	stream << std::to_string(x) << ',' << std::to_string(y);
	return stream.str();
}

auto vec2::parse(const std::string &value) -> vec2
{
	auto sep = value.find(',');
	auto x = value.substr(0, sep);
	auto y = value.substr(sep);
	return vec2(std::stoi(x), std::stoi(y));
}
