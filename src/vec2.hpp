#pragma once

#include <string>
#include <sstream>

class vec2
{
public:
	vec2(int x, int y);

	/** Format vec2 as x,y */
	[[nodiscard]] auto to_string() const -> std::string;

	/** Parse vec2 from string */
	static auto parse(const std::string &value) -> vec2;

	int x = 0;
	int y = 0;
};
