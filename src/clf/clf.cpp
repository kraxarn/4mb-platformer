#include "clf.hpp"

auto clf::level_type_string() const -> std::string
{
	switch (level_type)
	{
		case e::level_type::normal:
			return "normal";

		case e::level_type::boss:
			return "boss";

		default:
			return std::string();
	}
}
