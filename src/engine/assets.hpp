#pragma once

#include "res.hpp"
#include "clf/clf.hpp"
#include "engine/music.hpp"

#include <vector>

namespace ce
{
	class assets
	{
	public:
		assets();

		auto level(const std::string &path) -> clf;
		auto all_levels() -> std::vector<clf>;

		auto music(const std::string &path) -> music;

	private:
		cmrc::embedded_filesystem fs;
	};
}
