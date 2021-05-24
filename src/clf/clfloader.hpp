#pragma once

#include "clf/clf.hpp"

#include <string>

/**
 * Abstract CLF loader
 */
class clf_loader
{
public:
	/** Parse data as level */
	virtual auto parse(const std::string &data) -> clf = 0;

	/** Format level as a string */
	virtual auto to_string(const clf &level) -> std::string = 0;

protected:
	clf_loader() = default;
};
